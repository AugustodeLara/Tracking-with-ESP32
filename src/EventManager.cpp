#include "EventManager.h"

EventManager::EventManager() {
  // Construtor da classe, se necessário
}

void EventManager::addEvent(Event event) {
  eventQueue.add(event);
}

Event EventManager::getEvent() {
  return eventQueue.get(0);
}

void EventManager::removeEvent() {
  eventQueue.pop();
}

bool EventManager::isEmpty() {
  return eventQueue.size() == 0;
}
