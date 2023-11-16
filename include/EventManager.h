#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <LinkedList.h>
#include <Arduino.h>
#include "Event.h" // Inclua a nova classe Event

class EventManager {
public:
  EventManager();
  void addEvent(const Event& event);
  Event getEvent();  
  void removeEvent();
  bool isEmpty();
  void printAllEvents();
  LinkedList<Event>& getEventQueue(); 

private:
  LinkedList<Event> eventQueue;
};

#endif
