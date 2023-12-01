#include "planet.hpp"
#include "event.hpp"
#include "eventmanager.hpp"

Planet::Planet(float speed, float x_position): SpaceObject("static/icons/planet_medium.png", speed, x_position) {}
void Planet::onCollision() {
  if (!this->isCollided()) {
    Event event;
    event.type = Event::Type::CollisionWithPlanet;
    EventManager::getInstance()->emit(event);
    this->setCollided(true);
  }
}