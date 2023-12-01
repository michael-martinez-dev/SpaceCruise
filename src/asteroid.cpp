#include "asteroid.hpp"
#include "event.hpp"
#include "eventmanager.hpp"

Asteroid::Asteroid(float speed, float x_position): SpaceObject("static/icons/asteroid.png", speed, x_position) {}
void Asteroid::onCollision() {
  if (!this->isCollided()) {
    Event event;
    event.type = Event::Type::CollisionWithAstroid;
    EventManager::getInstance()->emit(event);
    this->setCollided(true);
  }
}