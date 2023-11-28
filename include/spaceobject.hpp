#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H
#include "rocketship.hpp"

class SpaceObject {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f direction;
    float speed;

public:
    SpaceObject(const std::string& texturePath, float speed, float x_position);
    sf::Sprite getSprite();
    bool isOutOfBound(float maxX, float maxY);
    virtual void update(float deltaTime, std::unique_ptr<Rocketship>& rocket);
    virtual void onCollision() = 0;
};

#endif //SPACEOBJECT_H
