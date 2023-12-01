#include "eventmanager.hpp"

EventManager* EventManager::instance;

EventManager* EventManager::getInstance() {
    if (instance == nullptr) {
        instance = new EventManager();
    }
    return instance;
}

void EventManager::subscribe(EventListener* listener) {
    listeners.push_back(listener);
}

void EventManager::emit(const Event& event) {
    for (auto& listener : this->listeners) {
        listener->onEvent(event);
    }
}
