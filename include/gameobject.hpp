#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics/Rect.hpp>


class GameObject {
  public:
    virtual sf::FloatRect getBoundingBox() const = 0;
};

#endif