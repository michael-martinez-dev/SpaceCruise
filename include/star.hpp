#ifndef STAR_HPP
#define STAR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Star {
private:
    sf::CircleShape shape;
    float depth;
    float speed;

public:
    Star(float x, float y, float radius, float depth);
    void update(float deltaTime, int rocketSpeed, int screenHeight, int screenWidth);
    sf::CircleShape getShape();
};

#endif