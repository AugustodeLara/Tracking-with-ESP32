#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <LinkedList.h>
#include <Arduino.h>  // Inclua esta biblioteca


struct Event {
  int controllerID;
  time_t timestamp;
  char* payload;
};

class EventManager {
public:
  EventManager();
  void addEvent(Event event);
  Event getEvent();
  void removeEvent();
  bool isEmpty();

private:
  LinkedList<Event> eventQueue;
};

#endif
