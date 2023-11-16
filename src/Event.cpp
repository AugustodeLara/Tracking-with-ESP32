#include "Event.h"

Event::Event() : controllerID(0), timestamp(0), payload(nullptr) {
    // Construtor padrão
}

Event::Event(int controllerID, time_t timestamp, const char* payload)
    : controllerID(controllerID), timestamp(timestamp), payload(payload) {
    // Construtor com argumentos
}

int Event::getControllerID() const {
    return controllerID;
}

void Event::setControllerID(int newControllerID) {
    controllerID = newControllerID;
}

time_t Event::getTimestamp() const {
    return timestamp;
}

void Event::setTimestamp(time_t newTimestamp) {
    timestamp = newTimestamp;
}

const char* Event::getPayload() const {
    return payload;
}

void Event::setPayload(const char* newPayload) {
    payload = newPayload;
}
