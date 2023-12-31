#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include "gameobject.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class SpaceObject : GameObject {
private:
    std::string texturePath;
    sf::Sprite sprite;
    sf::Vector2f direction;
    float speed;
    bool collided;

public:
    SpaceObject(const std::string& texturePath, float speed, float x_position);
    sf::Sprite getSprite() const override;
    bool isOutOfBound(float maxX, float maxY);
    bool isCollided() {return this->collided;};
    void setCollided(bool collided) {this->collided=collided;};
    virtual void update(float deltaTime, float rocketSpeed, float rocketRotation);
    virtual void onCollision() = 0;
    sf::FloatRect getBoundingBox() const override;
    float getCollisionRadius() const override;
};

#endif //SPACEOBJECT_H
