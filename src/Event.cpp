// Event.cpp
#include "Event.h"
#include "ClockCalendar.h"

Event::Event() : controllerID(ID_DEFAULT), payload(nullptr) {}

Event::Event(ControllerID controllerID, const String& timestamp, const char* payload)
    : controllerID(controllerID), timestamp(timestamp), payload(payload) {}

ControllerID Event::getControllerID() const {
    return controllerID;
}

void Event::setControllerID(ControllerID newControllerID) {
    controllerID = newControllerID;
}

String Event::getTimestamp() const {
    return timestamp;
}

void Event::setTimestamp(const String& newTimestamp) {
    timestamp = newTimestamp;
}

const char* Event::getPayload() const {
    return payload;
}

void Event::setPayload(const char* newPayload) {
    payload = newPayload;
}
