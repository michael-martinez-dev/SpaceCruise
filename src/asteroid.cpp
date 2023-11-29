#include "asteroid.hpp"

Asteroid::Asteroid(float speed, float x_position): SpaceObject("static/icons/asteroid.png", speed, x_position) {}
void Asteroid::onCollision() {
  if (!this->isCollided()) {
    printf("Boom!\n");
    this->setCollided(true);
  }
}