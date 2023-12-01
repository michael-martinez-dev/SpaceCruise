#include "game.hpp"
#include "rocketship.hpp"
#include "spaceobject.hpp"
#include "planet.hpp"
#include "asteroid.hpp"
#include "event.hpp"
#include "eventmanager.hpp"
#include <SFML/Graphics/Text.hpp>
#include <algorithm>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>

#define MAX_SPEED 10
#define BASE_COOLDOWN 5.0f

Game::Game() : window(sf::VideoMode(800, 600), "Space Cruise"),
               rocket(std::make_unique<Rocketship>(&this->window)),
               rng(static_cast<unsigned>(time(nullptr))),
               distX(0.0f, window.getSize().x),
               distSpeed(5, 15), timeSinceLastSpaceObject(0.0f) {
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

  for (std::size_t i = 0; i < messages.size(); ++i) {
    sf::Text text;
    text.setFont(this->font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(48);

    // Set the string from the vector
    text.setString(messages[i]);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    sf::Vector2u windowSize = this->window.getSize();
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    this->initMsgs.push_back(text);
  }
  this->initializeStars();
}

void Game::initializeStars() {
  int numberOfStars = 100;
  float maxDepth = 5.0f;

  for (int i = 0; i < numberOfStars; ++i) {
    float x = static_cast<float>(rand() % window.getSize().x);
    float y = static_cast<float>(rand() % window.getSize().y);
    float radius = 1.0f;
    float depth = 1.0f + static_cast<float>(rand()) / (static_cast<float>((float)RAND_MAX / (maxDepth - 1.0f))); // Random depth from 1.0 to maxDepth

    stars.emplace_back(x, y, radius, depth);
  }
}

void Game::run() {
  for (std::size_t i = 0; i < this->initMsgs.size(); i++) {
    this->window.draw(this->initMsgs[i]);
    this->window.display();
    this->window.clear();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  auto lastFrameTime = std::chrono::steady_clock::now();
  while (this->window.isOpen()) {
    sf::Event event;
    while (this->window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        this->window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
          this->rocket->turnRight();
        }
        else if (event.key.code == sf::Keyboard::Left) {
          this->rocket->turnLeft();
        }
        else if (event.key.code == sf::Keyboard::Up) {
          this->rocket->increaseShake();
        }
        else if (event.key.code == sf::Keyboard::Down) {
          this->rocket->decreaseShake();
        }
      }
    }

    this->render(&lastFrameTime);
  }
}

void Game::update(float deltaTime) {
  sf::Vector2u windowSize = this->window.getSize();
  this->timeSinceLastSpaceObject += deltaTime;
  for (auto& star : stars) {
    star.update(deltaTime, this->rocket->getSpeed(), windowSize.y, windowSize.x);
  }
  this->rocket->update();

  if(shouldAddNewSpaceObject()) {
    addRandomSpaceObject();
  }

  for (auto& obj : this->spaceObjects) {
    obj->update(deltaTime, rocket->getSpeed(), rocket->getSprite().getRotation());
    rocket->checkObjectCollisoin(*obj);
  }

  spaceObjects.erase(
      std::remove_if(spaceObjects.begin(), spaceObjects.end(),
                       [&](const std::unique_ptr<SpaceObject>& obj) {
                           return obj->isOutOfBound(windowSize.x, windowSize.y);
                       }),
      spaceObjects.end());
}

void Game::render(std::chrono::steady_clock::time_point *lastFrameTime) {
  this->window.clear();
  auto currentTime = std::chrono::steady_clock::now();
  float deltaTime = std::chrono::duration<float>(currentTime - *lastFrameTime).count();
  *lastFrameTime = currentTime;

  this->update(deltaTime);
  for (auto& star : stars) {
    this->window.draw(star.getShape());
  }
  for (const auto& obj : spaceObjects) {
    window.draw(obj->getSprite());
  }
  this->window.draw(this->rocket->getSprite());
  this->window.display();
}

void Game::addRandomSpaceObject() {
  float randomX = this->distX(this->rng);
  float randomSpeed = this->distSpeed(this->rng);
  sf::Vector2f startPosition(randomX, 0.0f);

  if (std::rand() % 3) {
    this->spaceObjects.push_back(std::make_unique<Asteroid>(randomSpeed, randomX));
  }
  else {
    this->spaceObjects.push_back(std::make_unique<Planet>(randomSpeed, randomX));
  }
}

bool Game::shouldAddNewSpaceObject() {
  float speedFactor = this->rocket->getSpeed() / MAX_SPEED;
  float dynamicCooldown = BASE_COOLDOWN / (1.0f + speedFactor); // BASE_COOLDOWN is the cooldown at minimum speed

  if (this->timeSinceLastSpaceObject >= dynamicCooldown) {
    this->timeSinceLastSpaceObject = 0.0f;
    return true;
  }
  return false;
}

void Game::onEvent(const Event& event) {
  if (event.type == Event::Type::CollisionWithPlanet) {
    printf("Refueling...\n");
  }
  else if (event.type == Event::Type::CollisionWithAstroid) {
    printf("BOOM\n");
  }
}
