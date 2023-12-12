#ifndef PLANET_HPP
#define PLANET_HPP

#include "spaceobject.hpp"

class Planet: public SpaceObject {
private:

public:
  Planet(float speed, float x_position);
  Planet(std::string imgPath, float speed, float x_position);
  void onCollision() override;
};

#endif //PLANET_HPP
