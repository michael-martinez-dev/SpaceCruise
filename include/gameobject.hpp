#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>


class GameObject {
  private:

  public:
    virtual sf::Sprite getSprite() const = 0;
    virtual sf::FloatRect getBoundingBox() const = 0;
    virtual float getCollisionRadius() const = 0;
};

#endif