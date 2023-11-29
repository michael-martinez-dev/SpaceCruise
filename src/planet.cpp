//
// Created by mmartinez on 11/28/23.
//

#include "planet.hpp"

Planet::Planet(float speed, float x_position): SpaceObject("static/icons/planet_medium.png", speed, x_position), collided(false) {}
void Planet::onCollision() {
  if (!this->collided) {
    printf("Refueling...\n");
    this->collided = true;
  }
}