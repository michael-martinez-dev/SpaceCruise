#ifndef EVENET_HPP
#define EVENET_HPP

class Event {
public:
    enum class Type {
        CollisionWithPlanet,
        CollisionWithAstroid,
        RocketOutOfFuel
    };
    Type type;
};

#endif //EVENET_HPP
