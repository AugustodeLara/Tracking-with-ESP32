// QueueEvents.cpp
#include "QueueEvents.h"

QueueEvents::Node::Node(const Event& event)
    : data(event), next(nullptr) {
}

QueueEvents::QueueEvents() : front(nullptr), rear(nullptr) {
}

QueueEvents::QueueEvents(const QueueEvents& other) : front(nullptr), rear(nullptr) {
  Node* current = other.front;
  while (current != nullptr) {
    enqueue(current->data);
    current = current->next;
  }
}

QueueEvents::~QueueEvents() {
  while (!isEmpty()) {
    dequeue();
  }
}

QueueEvents& QueueEvents::operator=(const QueueEvents& other) {
  if (this != &other) {
    while (!isEmpty()) {
      dequeue();
    }
    Node* current = other.front;
    while (current != nullptr) {
      enqueue(current->data);
      current = current->next;
    }
  }
  return *this;
}

void QueueEvents::enqueue(const Event& event) {
  Node* newNode = new Node(event);

  if (rear == nullptr) {
    front = rear = newNode;
  } else {
    rear->next = newNode;
    rear = newNode;
  }
}

Event QueueEvents::dequeue() {
  if (isEmpty()) {
    return Event();
  }

  Node* temp = front;
  Event data = temp->data;

  front = front->next;

  if (front == nullptr) {
    rear = nullptr;
  }

  delete temp;

  return data;
}

bool QueueEvents::isEmpty() {
  return front == nullptr;
}

size_t QueueEvents::size() {
  size_t count = 0;
  Node* current = front;

  while (current != nullptr) {
    count++;
    current = current->next;
  }

  return count;
}
