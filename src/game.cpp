#include "game.hpp"
#include "asteroid.hpp"
#include "event.hpp"
#include "eventmanager.hpp"
#include "planet.hpp"
#include "rocketship.hpp"
#include "spaceobject.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory>
#include <thread>

#define MAX_SPEED 10
#define BASE_COOLDOWN 20.0f
#define SCORE_DIV_CONSTANT 100
#define DEBUG true

bool debug = DEBUG;

Game::Game()
    : window(sf::VideoMode(800, 600), "Space Cruise"),
      rocket(std::make_unique<Rocketship>(&this->window)),
      rng(static_cast<unsigned>(time(nullptr))),
      distX(0.0f, window.getSize().x), distSpeed(5, 15),
      timeSinceLastSpaceObject(0.0f), timeSinceLastFuelDecrease(0.0f),
      rocketHit(false), score(0) {
  this->rocket->enableShake();
  EventManager::getInstance()->subscribe(this);
}

void Game::init() {
  if (!this->font.loadFromFile(
          "static/fonts/roboto_mono/static/RobotoMono-Medium.ttf")) {
    std::cout << "could not find font\n";
    exit(1);
  }
  std::vector<std::string> messages = {"3", "2", "1", "LAUNCH!"};
  this->preGameMsgs.clear();
  this->preGameMsgs.resize(0);
  this->initializePreGame(messages);
  this->initializeStars();
  this->spaceObjects.clear();
  this->spaceObjects.resize(0);
  this->rocket->resetFuel();
  this->timeSinceLastSpaceObject = 0.0f;
  this->timeSinceLastFuelDecrease = 0.0f;
  if (this->rocket->getLives() == 3) {
    this->score = 0;
  }
}

void Game::initializePreGame(std::vector<std::string> preGameMsgs) {
  for (std::size_t i = 0; i < this->preGameMsgs.size(); ++i) {
    sf::Text text;
    text.setFont(this->font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(48);

    // Set the string from the vector
    text.setString(preGameMsgs[i]);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);

    sf::Vector2u windowSize = this->window.getSize();
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    this->preGameMsgs.push_back(text);
  }
}

void Game::initializeStars() {
  int numberOfStars = 100;
  float maxDepth = 5.0f;

  for (int i = 0; i < numberOfStars; ++i) {
    float x = static_cast<float>(rand() % window.getSize().x);
    float y = static_cast<float>(rand() % window.getSize().y);
    float radius = 1.0f;
    float depth =
        1.0f + static_cast<float>(rand()) /
                   (static_cast<float>(
                       (float)RAND_MAX /
                       (maxDepth - 1.0f))); // Random depth from 1.0 to maxDepth

    stars.emplace_back(x, y, radius, depth);
  }
}

void Game::run() {
  while (this->play) {
    this->play = false;
    this->init();
    this->renderPreGame();
    auto lastFrameTime = std::chrono::steady_clock::now();
    while (!this->rocket->isDestroyed() && this->window.isOpen()) {
      this->handleEvents();
      this->render();
      if(!this->isPaused) {
        this->update(&lastFrameTime);
      }
    }
    this->renderPostGame();
  }
}

void Game::handleEvents() {
  sf::Event event;
  while (this->window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      this->window.close();
      exit(0);
    }
    if (event.type == sf::Event::KeyPressed) {
      if (this->rocket->isDestroyed()) {
        if (event.key.code == sf::Keyboard::C) {
          this->play = true;
          this->rocket->resetLives();
        } else if (event.key.code == sf::Keyboard::Q) {
          this->quit = true;
          this->window.close();
        }
        return;
      }
      if(!isPaused) {
        if (event.key.code == sf::Keyboard::Right) {
          this->rocket->turnRight();
        } else if (event.key.code == sf::Keyboard::Left) {
          this->rocket->turnLeft();
        } else if (event.key.code == sf::Keyboard::Up) {
          this->rocket->increaseShake();
        } else if (event.key.code == sf::Keyboard::Down) {
          this->rocket->decreaseShake();
        }
      }
      if (event.key.code == sf::Keyboard::D) {
        debug = !debug;
      } else if (event.key.code == sf::Keyboard::Space) {
        this->togglePause();
      }
    }
  }
}

void Game::update(std::chrono::steady_clock::time_point *lastFrameTime) {
  auto currentTime = std::chrono::steady_clock::now();
  float deltaTime =
      std::chrono::duration<float>(currentTime - *lastFrameTime).count();
  *lastFrameTime = currentTime;

  sf::Vector2u windowSize = this->window.getSize();
  this->timeSinceLastSpaceObject += deltaTime;
  this->timeSinceLastFuelDecrease += deltaTime;
  this->timeSincePopupStart += deltaTime;
  for (auto &star : stars) {
    star.update(deltaTime, this->rocket->getSpeed(), windowSize.y,
                windowSize.x);
  }
  this->rocket->update();

  if (shouldAddNewSpaceObject()) {
    addRandomSpaceObject();
  }

  for (auto &obj : this->spaceObjects) {
    if(obj != std::nullptr_t()) {
      obj->update(deltaTime, rocket->getSpeed(),
                  rocket->getSprite().getRotation());
      rocket->checkObjectCollisoin(*obj);
    }
  }

  if (this->timeSinceLastFuelDecrease >= 2) {
    this->rocket->decreaseFuel();
    this->timeSinceLastFuelDecrease = 0.0f;
    this->score += this->rocket->getSpeed();
  }
  this->rocket->checkFuel();
  if (this->score > 0) {
    this->rocket->setMinSpeed((short)this->score / SCORE_DIV_CONSTANT);
  }

  spaceObjects.erase(
      std::remove_if(spaceObjects.begin(), spaceObjects.end(),
                     [&](const std::unique_ptr<SpaceObject> &obj) {
                       return obj->isOutOfBound(windowSize.x, windowSize.y);
                     }),
      spaceObjects.end());

}

void Game::renderPreGame() {
  this->window.clear();
  for (std::size_t i = 0; i < this->preGameMsgs.size(); i++) {
    this->window.draw(this->preGameMsgs[i]);
    this->window.display();
    this->window.clear();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void Game::render() {
  this->window.clear();
  if (debug) {
    float rocketRadius = this->rocket->getCollisionRadius();
    sf::CircleShape rocketCircle(rocketRadius);
    rocketCircle.setPosition(this->rocket->getOriginalPosition() - sf::Vector2f(rocketRadius, rocketRadius));
    rocketCircle.setFillColor(sf::Color::Transparent);
    rocketCircle.setOutlineColor(sf::Color::Red);
    rocketCircle.setOutlineThickness(1);
    this->window.draw(rocketCircle);

    // Draw bounding boxes for space objects
    for (const auto& obj : spaceObjects) {
      float objectRadius = obj->getCollisionRadius();
      sf::CircleShape objectCircle(objectRadius);
      objectCircle.setPosition(obj->getSprite().getPosition() - sf::Vector2f(objectRadius, objectRadius));
      objectCircle.setFillColor(sf::Color::Transparent);
      objectCircle.setOutlineColor(sf::Color::Green);
      objectCircle.setOutlineThickness(1);
      this->window.draw(objectCircle);
    }
  }

  if(this->displayPopupText) {
    this->window.draw(*this->popupText);
    if (this->timeSincePopupStart > 2) {
      free(this->popupText);
      this->popupText = NULL;
      this->displayPopupText = false;
    }
  }

  if (this->isPaused) {
    sf::Text pauseText("||", this->font, 24);
    pauseText.setPosition(this->window.getSize().x / 2, this->window.getSize().y / 2);
    this->window.draw(pauseText);
  }

  this->renderStars();
  this->renderSpaceObjects();
  this->renderStats();

  if (this->rocketHit) {
    this->window.draw(this->rocket->getExplosion());
    this->window.display();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    this->rocketHit = false;
    this->init();
  } else {
    this->window.draw(this->rocket->getSprite());
    this->window.display();
  }
}

void Game::renderStars() {
  for (auto &star : stars) {
    this->window.draw(star.getShape());
  }
}

void Game::renderStats() {
  sf::Vector2u windowSize = this->window.getSize();

  sf::Text livesText;
  livesText.setFont(this->font);
  livesText.setFillColor(sf::Color::White);
  livesText.setCharacterSize(26);
  livesText.setString("Lives: " + std::to_string(this->rocket->getLives()) + "/" + std::to_string(this->rocket->MAX_LIVES));
  sf::FloatRect livesTextRect = livesText.getLocalBounds();
  livesText.setOrigin(livesTextRect.left + livesTextRect.width / 2.0f,
                      livesTextRect.top + livesTextRect.height / 2.0f);
  livesText.setPosition(livesTextRect.width / 2.0f + 10.0f, livesTextRect.height / 2.0f + 10.0f);
  this->window.draw(livesText);

  sf::Text fuelText;
  fuelText.setFont(this->font);
  if (this->rocket->getFuel() < 20) {
    fuelText.setFillColor(sf::Color::Red);
  }
  else {
    fuelText.setFillColor(sf::Color::White);
  }
  fuelText.setCharacterSize(26);
  fuelText.setString("Fuel: " + std::to_string(this->rocket->getFuel()) + "/" + std::to_string(this->rocket->MAX_FUEL));
  sf::FloatRect fuelTextRect = fuelText.getLocalBounds();
  fuelText.setOrigin(fuelTextRect.left + fuelTextRect.width / 2.0f,
                     fuelTextRect.top + fuelTextRect.height / 2.0f);
  fuelText.setPosition(fuelTextRect.width / 2.0f + 10.0f, fuelTextRect.height / 2.0f + 10.0f * 4);
  this->window.draw(fuelText);

  sf::Text speedText;
  speedText.setFont(this->font);
  speedText.setFillColor(sf::Color::White);
  speedText.setCharacterSize(26);
  speedText.setString("Speed: " + std::to_string(this->rocket->getSpeed()));
  sf::FloatRect speedTextRect = speedText.getLocalBounds();
  speedText.setOrigin(speedTextRect.left + speedTextRect.width / 2.0f,
                     speedTextRect.top + speedTextRect.height / 2.0f);
  speedText.setPosition(speedTextRect.width / 2.0f + 10.0f, speedTextRect.height / 2.0f + 10.0f * 7);
  this->window.draw(speedText);


  sf::Text scoreText;
  scoreText.setFont(this->font);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setCharacterSize(26);
  scoreText.setString("Score: " + std::to_string(this->score));
  sf::FloatRect scoreTextRect = scoreText.getLocalBounds();
  scoreText.setOrigin(scoreTextRect.left + scoreTextRect.width / 2.0f,
                      scoreTextRect.top + scoreTextRect.height / 2.0f);
  scoreText.setPosition(scoreTextRect.width / 2.0f + 10.0f, scoreTextRect.height / 2.0f + 10.0f * 10);
  this->window.draw(scoreText);
}

void Game::renderSpaceObjects() {
  for (const auto &obj : spaceObjects) {
    window.draw(obj->getSprite());
  }
}

void Game::renderPostGame() {
  sf::Text text;
  text.setFont(this->font);
  text.setFillColor(sf::Color::White);
  text.setCharacterSize(48);

  text.setString("Final Score: " + std::to_string(this->score));

  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f,
                 textRect.top + textRect.height / 2.0f);
  sf::Vector2u windowSize = this->window.getSize();
  text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

  this->window.clear();
  this->window.display();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  this->window.draw(text);
  this->window.display();
  std::this_thread::sleep_for(std::chrono::seconds(5));

  text.setString("GAME OVER");

  textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f,
                 textRect.top + textRect.height / 2.0f);
  text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

  for (int i = 0; i < 3; i++) {
    this->window.clear();
    this->window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    this->window.draw(text);
    this->window.display();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  text.setString("Press 'c' to continue\n    or 'q' to quit");
  text.setCharacterSize(24);

  textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f,
                 textRect.top + textRect.height / 2.0f);

  windowSize = this->window.getSize();
  text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
  this->window.clear();
  this->window.display();
  this->window.draw(text);
  this->window.display();
  while(!(this->play || this->quit)) {
    handleEvents();
  }
}

void Game::addRandomSpaceObject() {
  float randomX = this->distX(this->rng);
  float randomSpeed = this->distSpeed(this->rng);
  sf::Vector2f startPosition(randomX, 0.0f);

  if (std::rand() % 3) {
    this->spaceObjects.push_back(
        std::make_unique<Asteroid>(randomSpeed * 2, randomX));
  } else {
    this->spaceObjects.push_back(
        std::make_unique<Planet>(randomSpeed, randomX));
  }
}

bool Game::shouldAddNewSpaceObject() {
  float speedFactor = this->rocket->getSpeed();
  float dynamicCooldown = BASE_COOLDOWN / speedFactor;

  if (this->timeSinceLastSpaceObject >= dynamicCooldown) {
    this->timeSinceLastSpaceObject = 0.0f;
    return true;
  }
  return false;
}

void Game::onEvent(const Event &event) {
  if (event.type == Event::Type::CollisionWithPlanet) {
    this->rocket->increseFuel();
    sf::Vector2f position = this->rocket->getSprite().getPosition();
    position.y += this->window.getSize().y / 10;
    this->popup("+25 fuel", sf::Color::Green, position);
    this->timeSinceLastFuelDecrease = 0.0f;
  } else if (event.type == Event::Type::CollisionWithAstroid) {
    rocketHit = true;
    this->rocket->removeLife();
  } else if (event.type == Event::Type::RocketOutOfFuel) {
    rocketHit = true;
    sf::Vector2f position = this->rocket->getSprite().getPosition();
    position.y += this->window.getSize().y / 10;
    this->popup("Out of fuel!", sf::Color::Red, position);
    this->rocket->removeLife();
    this->rocket->resetFuel();
  }
}

void Game::popup(std::string msg, sf::Color color, sf::Vector2f position) {
  this->popupText = new sf::Text();
  this->popupText->setFont(this->font);
  this->popupText->setFillColor(color);
  this->popupText->setString(msg);
  sf::FloatRect textRect = this->popupText->getLocalBounds();
  this->popupText->setOrigin(textRect.left + textRect.width / 2.0f,
                 textRect.top + textRect.height / 2.0f);
  sf::Vector2u windowSize = this->window.getSize();
  this->popupText->setPosition(position.x, position.y);

  this->displayPopupText = true;
  this->timeSincePopupStart = 0.0f;
}

void Game::popup(sf::Sprite sprite, sf::Color color, sf::Vector2f position) {

}
