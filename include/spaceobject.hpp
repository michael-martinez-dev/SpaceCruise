#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

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
    virtual void update(float deltaTime, float rocketSpeed, float rocketRotation);
    virtual void onCollision() = 0;
};

#endif //SPACEOBJECT_H
