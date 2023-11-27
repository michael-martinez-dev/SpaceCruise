#include "rocketship.hpp"
#define ROCKET_ICON_PATH "static/icons/rocketship.png"
#define MAX_DEGREE_LEFT 315
#define MAX_DEGREE_RIGHT 45
#define TURN_DEGREES 45
#define TRUE 1
#define FALSE 0

Rocketship::Rocketship(sf::RenderWindow *window) {
  this->window = window;
  if (!this->texture.loadFromFile(ROCKET_ICON_PATH)) {
    printf("could not find rocket\n");
    exit(1);
  }
  this->sprite.setTexture(this->texture);
  sf::Vector2u windowSize = this->window->getSize();
  sf::Vector2u textureSize = this->texture.getSize();
  this->sprite.setPosition((windowSize.x / 2),
                           (windowSize.y / 2));
  originalPosition = this->sprite.getPosition();
  sf::FloatRect bounds = this->sprite.getLocalBounds();
  this->sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

sf::Sprite Rocketship::getSprite() {
  return this->sprite;
}

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

void Rocketship::enableShake() { this->shakeOn = TRUE; }

void Rocketship::disableShake() { this->shakeOn = FALSE; }

void Rocketship::update() {
  if (this->shakeOn) {
    float offsetX =
        (std::rand() % this->shakeIntensity) - (this->shakeIntensity / 2.0f);
    float offsetY =
        (std::rand() % this->shakeIntensity) - (this->shakeIntensity / 2.0f);
    sprite.setPosition(originalPosition + sf::Vector2f(offsetX, offsetY));
  }
}

void Rocketship::noShake() {
  this->shakeIntensity = 0;
}

void Rocketship::decreaseShake() {
  if (this->shakeIntensity > 1) {
    this->shakeIntensity--;
  }
}

void Rocketship::increaseShake() {
  if(this->shakeOn && this->shakeIntensity < 10) {
    this->shakeIntensity++;
  }
}

int Rocketship::getSpeed() {
  return this->shakeIntensity;
}
