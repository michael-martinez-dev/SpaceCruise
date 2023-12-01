#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <vector>
#include "eventlistener.hpp"

class EventManager {
private:
    static EventManager* instance;
    EventManager() {};
    std::vector<EventListener*> listeners;

public:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    static EventManager* getInstance();
    void subscribe(EventListener* listener);
    void emit(const Event& event);
};

#endif //EVENTMANAGER_HPP
