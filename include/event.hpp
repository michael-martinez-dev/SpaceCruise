#ifndef EVENET_HPP
#define EVENET_HPP

class Event {
public:
    enum class Type {
        CollisionWithPlanet,
        CollisionWithAstroid,
    };
    Type type;
};

#endif //EVENET_HPP
