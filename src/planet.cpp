#include "planet.hpp"
#include "event.hpp"
#include "eventmanager.hpp"

Planet::Planet(float speed, float x_position): SpaceObject(std::rand() % 2 == 0 ? "static/icons/planet_medium.png" : "static/icons/planet2_medium.png", speed, x_position) {}
Planet::Planet(std::string imgPath, float speed, float x_position): SpaceObject(imgPath, speed, x_position) {}
void Planet::onCollision() {
  if (!this->isCollided()) {
    Event event;
    event.type = Event::Type::CollisionWithPlanet;
    EventManager::getInstance()->emit(event);
    this->setCollided(true);
  }
}