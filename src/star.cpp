#include "star.hpp"

Star::Star(float x, float y, float radius, float depth)
    : depth(depth), speed(1.0f / depth) {
    this->shape.setRadius(radius);
    this->shape.setPosition(x, y);
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOrigin(radius, radius);
}

void Star::update(float deltaTime, int rocketSpeed, int screenHeight, int screenWidth) {
    sf::Vector2f position = this->shape.getPosition();

    position.y += this->speed * deltaTime * rocketSpeed;

    if (position.y > screenHeight) {
        position.y = 0;
        position.x = static_cast<float>(rand() % screenWidth);
    }

    this->shape.setPosition(position);
}

sf::CircleShape Star::
getShape() {
    return this->shape;
}
