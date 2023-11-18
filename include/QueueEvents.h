// QueueEvents.h
#ifndef QUEUE_EVENTS_H
#define QUEUE_EVENTS_H

#include "Event.h"

class QueueEvents {
public:
  QueueEvents();
  QueueEvents(const QueueEvents& other);
  ~QueueEvents();

  QueueEvents& operator=(const QueueEvents& other);

  void enqueue(const Event& event);
  Event dequeue();
  bool isEmpty();
  size_t size(); 

private:
  class Node {
  public:
    Event data;
    Node* next;
    Node(const Event& event);
  };

  Node* front;
  Node* rear;
};

#endif
