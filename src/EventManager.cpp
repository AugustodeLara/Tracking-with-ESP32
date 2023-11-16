#include "EventManager.h"

EventManager::EventManager() {
  // Construtor da classe, se necessário
}

void EventManager::addEvent(const Event& event) {
  eventQueue.add(event);  // Adiciona o evento à fila
}

Event EventManager::getEvent() {
    if (eventQueue.size() > 0) {
        Event event = eventQueue.get(0);
        eventQueue.pop();
        return event;
    } else {
        // Retornar um Event padrão ou lançar uma exceção, dependendo do seu design
        return Event();
    }
}

void EventManager::removeEvent() {
  if (eventQueue.size() > 0) {
    eventQueue.pop();
  }
}

bool EventManager::isEmpty() {
  return eventQueue.size() == 0;
}
