// EventManager.cpp
#include "EventManager.h"
#include "ClockCalendar.h" // Inclua ClockCalendar aqui


EventManager::EventManager(std::shared_ptr<ClockCalendar> clockCalendar) : clockCalendar(clockCalendar) {
    clockCalendar = clockCalendar;
    // Construtor da classe, se necessário
}


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

size_t EventManager::getSizeQueue() {
    return eventQueue.size();
}

void EventManager::printAllEvents() {
    Serial.println("Elementos na fila do EventManager:");

    // Crie uma cópia temporária da fila para evitar removê-la
    QueueEvents tempQueue = eventQueue;

     while (!tempQueue.isEmpty()) {
        Event event = tempQueue.dequeue();
        String timestampString = event.getTimestamp();

        Serial.print("ID do Controlador: ");
        Serial.print(event.getControllerID());
        Serial.print(", Data/Hora: ");
        Serial.println(timestampString);
    }

    Serial.println("Fim da fila do EventManager");
}

QueueEvents EventManager::getEventQueue() {
    return eventQueue;  // Agora retorna uma cópia da fila
}
