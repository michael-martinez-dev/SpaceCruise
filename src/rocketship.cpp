#include "rocketship.hpp"
#include "event.hpp"
#include "eventmanager.hpp"
#include "gameobject.hpp"
#include "spaceobject.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <cmath>
#include <thread>

#define ROCKET_ICON_PATH "static/icons/rocketship.png"
#define EXPLOSION_ICON_PATH "static/icons/explosion.png"
#define MAX_DEGREE_LEFT 315
#define MAX_DEGREE_RIGHT 45
#define TURN_DEGREES 45
#define REFUEL_AMOUNT 25

Rocketship::Rocketship(sf::RenderWindow *window) {
  this->window = window;

  // Rocket Icon
  if (!this->texture.loadFromFile(ROCKET_ICON_PATH)) {
    printf("could not find rocket\n");
    exit(1);
  }
  this->sprite.setTexture(this->texture);
  sf::Vector2u windowSize = this->window->getSize();
  sf::Vector2u textureSize = this->texture.getSize();
  this->sprite.setPosition((windowSize.x / 2),
                           (windowSize.y - windowSize.y / 5));
  this->originalPosition = this->sprite.getPosition();
  sf::FloatRect bounds = this->sprite.getLocalBounds();
  this->sprite.setOrigin(bounds.width / 2, bounds.height / 2);
  this->collisionBox = this->sprite.getGlobalBounds();

  // Explosion icon
  if (!this->explosion_texture.loadFromFile(EXPLOSION_ICON_PATH)) {
    printf("could not find explosion\n");
    exit(1);
  }
  this->explosion_sprite.setTexture(this->explosion_texture);
  this->explosion_sprite.setPosition((windowSize.x / 2),
                                     (windowSize.y - windowSize.y / 5));
  bounds = this->explosion_sprite.getLocalBounds();
  this->explosion_sprite.setOrigin(bounds.width / 2, bounds.height / 2);

}

sf::Sprite Rocketship::getSprite() const { return this->sprite; }

void Rocketship::turnRight() {
  if (sprite.getRotation() != MAX_DEGREE_RIGHT) {
    sprite.rotate(TURN_DEGREES);
  }
}

void Rocketship::turnLeft() {
  if (sprite.getRotation() != MAX_DEGREE_LEFT) {
    sprite.rotate(-TURN_DEGREES);
  }
}

void Rocketship::enableShake() { this->shakeOn = true; }

void Rocketship::disableShake() { this->shakeOn = false; }

void Rocketship::update() {
  if (this->shakeOn) {
    float offsetX =
        (std::rand() % this->shakeIntensity) - (this->shakeIntensity / 2.0f);
    float offsetY =
        (std::rand() % this->shakeIntensity) - (this->shakeIntensity / 2.0f);
    sprite.setPosition(originalPosition + sf::Vector2f(offsetX, offsetY));
  }
}

void Rocketship::noShake() { this->shakeIntensity = 0; }

void Rocketship::decreaseShake() {
  if (this->shakeIntensity > 1 && this->shakeIntensity > this->minSpeed) {
    this->shakeIntensity--;
  }
}

void Rocketship::increaseShake() {
  if (this->shakeOn && this->shakeIntensity < this->MAX_SPEED) {
    this->shakeIntensity++;
  }
}

int Rocketship::getSpeed() {
  if (this->shakeIntensity < this->minSpeed) {
    return this->minSpeed;
  }
  return this->shakeIntensity;
}

void Rocketship::checkObjectCollisoin(SpaceObject& obj) {
  if (this->areColliding(obj)) {
    obj.onCollision();
  }
}



void Rocketship::checkFuel() {
  if (this->fuel == 0) {
    Event event;
    event.type = Event::Type::RocketOutOfFuel;
    EventManager::getInstance()->emit(event);
  }
}

sf::Sprite Rocketship::getExplosion() { return this->explosion_sprite; }

short Rocketship::getFuel() { return this->fuel; }

void Rocketship::increseFuel() {
  if (this->fuel <= this->MAX_FUEL) {
    this->fuel += REFUEL_AMOUNT;
    if (this-> fuel > this->MAX_FUEL) {
      this->fuel = this->MAX_FUEL;
    }
  }
}

void Rocketship::decreaseFuel() {
  if (this->fuel > 0) {
    this->fuel -= this->shakeIntensity / 2;
  }
  if (this->fuel < 0) {
    this->fuel = 0;
  }
}

void Rocketship::resetFuel() { this->fuel = this->MAX_FUEL; }

void Rocketship::removeLife() {
  if (this->lives > 0) {
    this->lives--;
  }
}

int Rocketship::getLives() { return this->lives; }

void Rocketship::resetLives() { this->lives = 3; }

bool Rocketship::isDestroyed() { return this->lives == 0; }

sf::FloatRect Rocketship::getBoundingBox() const {
  return this->collisionBox;
};

void Rocketship::setMinSpeed(short speed) {
  if (this->minSpeed < this->MAX_SPEED) {
    this->minSpeed = speed;
  }
}

short Rocketship::getMinSpeed() {
  if (this->minSpeed < this->MAX_SPEED) {
    return this->minSpeed;
  }
  return this->MAX_SPEED;
}

float Rocketship::getCollisionRadius() const {
  return this->texture.getSize().y / 2;
}

sf::Vector2f Rocketship::getOriginalPosition() {
  return this->originalPosition;
}

bool Rocketship::areColliding(const SpaceObject& obj) {
  sf::Vector2f positionSelf = this->originalPosition;
  sf::Vector2f position2Obj = obj.getSprite().getPosition();
  float dx = positionSelf.x - position2Obj.x;
  float dy = positionSelf.y - position2Obj.y;
  float dist = std::sqrt(dx * dx + dy * dy);
  return dist < (this->getCollisionRadius() + obj.getCollisionRadius());
}
