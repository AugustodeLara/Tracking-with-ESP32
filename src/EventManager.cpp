#include "EventManager.h"
#include <TimeLib.h>


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


void EventManager::printAllEvents() {
    Serial.println("Elementos na fila do EventManager:");
    for (int i = 0; i < eventQueue.size(); ++i) {
        Event event = eventQueue.get(i);
        Serial.print("ID do Controlador: ");
        Serial.print(event.getControllerID());
        Serial.print(", Data/Hora: ");
        Serial.print(hour(event.getTimestamp()));
        Serial.print(":");
        Serial.print(minute(event.getTimestamp()));
        Serial.print(":");
        Serial.println(second(event.getTimestamp()));
    }
    Serial.println("Fim da fila do EventManager");
}

LinkedList<Event>& EventManager::getEventQueue() {
    return eventQueue;
}