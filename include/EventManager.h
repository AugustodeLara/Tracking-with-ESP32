// EventManager.h
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <memory>  // Adicione esta linha
#include "QueueEvents.h"
#include "Event.h"
#include "ClockCalendar.h"
#include "Arduino.h"


class EventManager {
public:
    EventManager();
    EventManager(std::shared_ptr<ClockCalendar> clockCalendar);
    void addEvent(const Event& event);
    Event getEvent();  
    void removeEvent();
    bool isEmpty();
    void printAllEvents();
    size_t getSizeQueue();

    QueueEvents getEventQueue();  // Modificado para retornar uma cópia
private:
    QueueEvents eventQueue;
    std::shared_ptr<ClockCalendar> clockCalendar;  // Adicionando a declaração do membro clockCalendar aqui
};

#endif // EVENT_MANAGER_H
