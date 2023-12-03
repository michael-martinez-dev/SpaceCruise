#ifndef ROCKETSHIP_H
#define ROCKETSHIP_H

#include "spaceobject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <sys/types.h>

class Rocketship {
private:
  sf::RenderWindow *window;
  sf::Vector2f originalPosition;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Texture explosion_texture;
  sf::Sprite explosion_sprite;
  bool shakeOn = false;
  ushort shakeIntensity = 4;
  static const ushort MAX_FUEL = 100;
  ushort fuel = MAX_FUEL;
  ushort lives = 3;

public:
  Rocketship(sf::RenderWindow *window);
  sf::Sprite getSprite();
  void turnLeft();
  void turnRight();
  void enableShake();
  void disableShake();
  void update();
  void noShake();
  void decreaseShake();
  void increaseShake();
  int getSpeed();
  void checkObjectCollisoin(SpaceObject& obj);
  sf::Sprite getExplosion();
  ushort getFuel();
  void increseFuel();
  void decreaseFuel();
  void removeLife();
  void resetLives();
  bool isDestroyed();
};

#endif
