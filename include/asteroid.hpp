#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "spaceobject.hpp"
class Asteroid: public SpaceObject {
    private:
    
    public:
    Asteroid(float speed, float x_position);
    void onCollision() override;  
};

#endif // ASTEROID_HPP