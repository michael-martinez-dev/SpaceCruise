//
// Created by mmartinez on 11/28/23.
//

#ifndef PLANET_HPP
#define PLANET_HPP

#include "spaceobject.hpp"

class Planet: public SpaceObject {
private:
  bool collided;

public:
    Planet(float speed, float x_position);
    void onCollision() override;
};

#endif //PLANET_HPP
