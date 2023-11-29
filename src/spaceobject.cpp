#include "spaceobject.hpp"
#include "rocketship.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#define MAX_DEGREE_LEFT 315
#define MAX_DEGREE_RIGHT 45

SpaceObject::SpaceObject(const std::string& texturePath, float speed, float x_position) {
    sf::Vector2f startPosition(x_position, 0.0f);
    this->texture.loadFromFile(texturePath);
    texture.loadFromFile(texturePath);
    this->sprite.setTexture(texture);
    this->sprite.setPosition(startPosition);
    this->speed = speed;
    this->collided = false;
}

sf::Sprite SpaceObject::getSprite() {
    return this->sprite;
}

bool SpaceObject::isOutOfBound(float maxX, float maxY) {
  sf::Vector2f position = this->sprite.getPosition();
  return position.x < 0 || position.y < 0 ||
         position.x > maxX || position.y > maxY;
}

void SpaceObject::update(float deltaTime, float rocketSpeed, float rocketRotation) {
    sf::Vector2f position = this->sprite.getPosition();
    float rocketSpeedInfluence = rocketSpeed;

    if (rocketRotation != 0) {
        rocketSpeedInfluence /= 2;
        if (rocketRotation == MAX_DEGREE_LEFT) {
            position.x += this->speed * deltaTime * rocketSpeedInfluence;
        }
        else if (rocketRotation == MAX_DEGREE_RIGHT) {
            position.x -= this->speed * deltaTime * rocketSpeedInfluence;
        }
    }
    position.y += this->speed * deltaTime * rocketSpeedInfluence;

    this->sprite.setPosition(position);
}
