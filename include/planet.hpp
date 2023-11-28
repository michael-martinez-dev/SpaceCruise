//
// Created by mmartinez on 11/28/23.
//

#ifndef PLANET_HPP
#define PLANET_HPP

#include "spaceobject.hpp"

class Planet: public SpaceObject {
private:

public:
    Planet(float speed, float x_position): SpaceObject("static/icons/planet_medium.png", speed, x_position) {}
    void onCollision() override {
        printf("Refueling...");
    }
};

#endif //PLANET_HPP
