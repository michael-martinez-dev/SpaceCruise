#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>


class GameObject {
  private:

  public:
    virtual sf::FloatRect getBoundingBox() const = 0;
};

#endif