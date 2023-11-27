#include "game.hpp"
#include "rocketship.hpp"
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>

Game::Game() : window(sf::VideoMode(800, 600), "Space Cruise") {
  this->rocket = std::make_unique<Rocketship>(&this->window);
  this->rocket->enableShake();
}

void Game::init() {
  if (!this->font.loadFromFile(
          "static/fonts/roboto_mono/static/RobotoMono-Medium.ttf")) {
    std::cout << "could not find font\n";
    exit(1);
  }
  for (std::size_t i = 0; i < 3; ++i) {
    sf::Text text;
    text.setFont(this->font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(48);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    sf::Vector2u windowSize = this->window.getSize();
    text.setPosition((windowSize.x / 2 - textRect.width),
                             (windowSize.y / 2 - textRect.height));
    this->initMsgs.push_back(text);
  }
  this->initMsgs[0].setString("3");
  this->initMsgs[1].setString("2");
  this->initMsgs[2].setString("1");
  
  this->initializeStars();
}

void Game::initializeStars() {
  int numberOfStars = 100; // Adjust based on desired star density
  float maxDepth = 5.0f;   // Adjust for parallax effect range

  for (int i = 0; i < numberOfStars; ++i) {
    float x = static_cast<float>(rand() % window.getSize().x);
    float y = static_cast<float>(rand() % window.getSize().y);
    float radius = 1.0f; // Smaller stars for a more realistic look
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
  for (auto& star : stars) {
    star.update(deltaTime, this->rocket->getSpeed(), windowSize.y, windowSize.x);
  }
  this->rocket->update();
}

void Game::render(std::chrono::steady_clock::time_point *lastFrameTime) {
  this->window.clear();
  auto currentTime = std::chrono::steady_clock::now();
  float deltaTime = std::chrono::duration<float>(currentTime - *lastFrameTime).count();
  *lastFrameTime = currentTime;

  this->update(deltaTime);
  for (auto& star : stars) {
    star.draw(window);
  }
  this->window.draw(this->rocket->getSprite());
  this->window.display();
}
