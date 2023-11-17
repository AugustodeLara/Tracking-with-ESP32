// EventManager.cpp
#include "EventManager.h"
#include <TimeLib.h>

EventManager::EventManager() {
  // Construtor da classe, se necessário
}

void EventManager::addEvent(const Event& event) {
    eventQueue.enqueue(event);
}

Event EventManager::getEvent() {
    return eventQueue.dequeue();
}

void EventManager::removeEvent() {
    eventQueue.dequeue();
}

bool EventManager::isEmpty() {
  return eventQueue.isEmpty();
}

void EventManager::printAllEvents() {
    Serial.println("Elementos na fila do EventManager:");

    // Crie uma cópia temporária da fila para evitar removê-la
    QueueEvents tempQueue = eventQueue;

    while (!tempQueue.isEmpty()) {
        Event event = tempQueue.dequeue();
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

QueueEvents EventManager::getEventQueue() {
    return eventQueue;  // Agora retorna uma cópia da fila
}
