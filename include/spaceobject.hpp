#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H
#include "rocketship.hpp"

class SpaceObject {
private:
    sf::Sprite sprite;
    sf::Vector2f direction;
    float speed;

public:
    SpaceObject(const std::string& texturePath, float speed);
    virtual void update(const Rocketship& rocket);
    virtual void onCollision() = 0;
};

#endif //SPACEOBJECT_H
