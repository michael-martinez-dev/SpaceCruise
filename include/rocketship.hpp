#ifndef ROCKETSHIP_H
#define ROCKETSHIP_H

#include "gameobject.hpp"
#include "spaceobject.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Rocketship : GameObject {
private:
  sf::RenderWindow *window;
  sf::Vector2f originalPosition;
  sf::Sprite sprite;
  sf::Sprite explosion_sprite;
  sf::FloatRect collisionBox;
  bool shakeOn = false;
  short minSpeed = 0;
  short shakeIntensity = 4;
  short fuel = MAX_FUEL;
  short lives = MAX_LIVES;

  bool areColliding(const SpaceObject& obj);

public:
  static const short MAX_FUEL = 100;
  static const short MAX_LIVES = 3;
  static const short MAX_SPEED = 25;
  Rocketship(sf::RenderWindow *window);
  sf::Sprite getSprite() const override;
  void turnLeft();
  void turnRight();
  void enableShake();
  void disableShake();
  void update();
  void noShake();
  void decreaseShake();
  void increaseShake();
  short getMinSpeed();
  void setMinSpeed(short speed);
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
  sf::FloatRect getBoundingBox() const override;
  sf::Vector2f getOriginalPosition();
float getCollisionRadius() const override;
};

#endif
