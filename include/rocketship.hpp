#ifndef ROCKETSHIP_H
#define ROCKETSHIP_H

#include "gameobject.hpp"
#include "spaceobject.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Rocketship : GameObject {
private:
  sf::RenderWindow *window;
  sf::Vector2f originalPosition;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Texture explosion_texture;
  sf::Sprite explosion_sprite;
  sf::FloatRect collisionBox;
  bool shakeOn = false;
  short shakeIntensity = 4;
  short fuel = MAX_FUEL;
  short lives = MAX_LIVES;

public:
  static const short MAX_FUEL = 100;
  static const short MAX_LIVES = 3;
  static const short MAX_SPEED = 20;
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
  void checkFuel();
  sf::Sprite getExplosion();
  short getFuel();
  void increseFuel();
  void decreaseFuel();
  void resetFuel();
  void removeLife();
  int getLives();
  void resetLives();
  bool isDestroyed();
  sf::FloatRect getBoundingBox() const;
};

#endif
