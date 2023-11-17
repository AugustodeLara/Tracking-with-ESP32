// EventManager.h
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "QueueEvents.h"
#include "Event.h"

class EventManager {
public:
  EventManager();
  void addEvent(const Event& event);
  Event getEvent();  
  void removeEvent();
  bool isEmpty();
  void printAllEvents();
  QueueEvents getEventQueue();  // Modificado para retornar uma cópia

private:
  QueueEvents eventQueue;
};

#endif
