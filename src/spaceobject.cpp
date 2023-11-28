#include "spaceobject.hpp"
#include "rocketship.hpp"
#include <SFML/System/Vector2.hpp>

#define MAX_DEGREE_LEFT 315
#define MAX_DEGREE_RIGHT 45

SpaceObject::SpaceObject(const std::string& texturePath, float speed) {
    this->texture.loadFromFile(texturePath);
    texture.loadFromFile(texturePath);
    this->sprite.setTexture(texture);
    this->speed = speed;
}

sf::Sprite SpaceObject::getSprite() {
    return this->sprite;
}

bool SpaceObject::isOutOfBound(float maxX, float maxY) {
  sf::Vector2f position = this->sprite.getPosition();
  return position.x < 0 || position.y < 0 ||
         position.x > maxX || position.y > maxY;
}

void SpaceObject::update(float deltaTime, std::unique_ptr<Rocketship>& rocket) {
    sf::Vector2f position = this->sprite.getPosition();
    float rocketSpeedInfluence = rocket->getSpeed();

    if (rocket->getSprite().getRotation() != 0) {
        rocketSpeedInfluence /= 2;
        if (rocket->getSprite().getRotation() == MAX_DEGREE_LEFT) {
            position.x += this->speed * deltaTime * rocketSpeedInfluence;
        }
        else if (rocket->getSprite().getRotation() == MAX_DEGREE_RIGHT) {
            position.x -= this->speed * deltaTime * rocketSpeedInfluence;
        }
    }
    position.y += this->speed * deltaTime * rocketSpeedInfluence;

    this->sprite.setPosition(position);
}
