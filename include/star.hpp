#ifndef STAR_HPP
#define STAR_HPP

#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Star {
private:
    sf::CircleShape shape;  // Represents the star visually
    float depth;            // Depth factor for parallax effect
    float speed;            // Speed at which the star moves

public:
    // Constructor
    Star(float x, float y, float radius, float depth) 
        : depth(depth), speed(1.0f / depth) { // Speed inversely proportional to depth for parallax
        shape.setRadius(radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White); // Default color

        // Set the origin to the center for more natural rotation (optional)
        shape.setOrigin(radius, radius);
    }

    // Update the star's position; deltaTime is the time elapsed since the last update
    void update(float deltaTime, int rocketSpeed, int screenHeight, int screenWidth) {
        sf::Vector2f position = shape.getPosition();

        // Vertical movement (can be adjusted for horizontal or other types of movement)
        position.y += this->speed * deltaTime * rocketSpeed;

        // Wrap around logic for infinite effect
        if (position.y > screenHeight) { // screenHeight should be defined in your Game class or as a global
            position.y = 0;
            position.x = static_cast<float>(rand() % screenWidth); // screenWidth similar to screenHeight
        }

        // Update the position of the star
        shape.setPosition(position);
    }

    // Render the star
    void draw(sf::RenderWindow& window) {
      window.draw(shape);
    }

    // Additional methods as needed (e.g., getters, setters, etc.)
};

#endif