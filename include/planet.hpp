//
// Created by mmartinez on 11/28/23.
//

#ifndef PLANET_HPP
#define PLANET_HPP

#include "spaceobject.hpp"

class Planet: SpaceObject {
private:

public:
Planet(): SpaceObject("static/icons/planet_medium.png", 10) {}
void onCollision() override {
  printf("Refueling...");
}
};

#endif //PLANET_HPP
