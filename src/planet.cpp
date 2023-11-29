#include "planet.hpp"

Planet::Planet(float speed, float x_position): SpaceObject("static/icons/planet_medium.png", speed, x_position) {}
void Planet::onCollision() {
  if (!this->isCollided()) {
    printf("Refueling...\n");
    this->setCollided(true);
  }
}