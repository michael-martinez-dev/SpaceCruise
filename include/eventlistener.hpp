#ifndef EVENTLISTENER_HPP
#define EVENTLISTENER_HPP

#include "event.hpp"

class EventListener {
public:
    virtual void onEvent(const Event& event) = 0;
};

#endif //EVENTLISTENER_HPP
