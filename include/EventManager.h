#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <LinkedList.h>
#include <Arduino.h>
#include "Event.h" // Inclua a nova classe Event

class EventManager {
public:
  EventManager();
  void addEvent(const Event& event);
  Event getEvent();  // Modificado para retornar Event
  void removeEvent();
  bool isEmpty();

private:
  LinkedList<Event> eventQueue;
};

#endif
