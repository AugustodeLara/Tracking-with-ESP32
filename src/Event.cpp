// Event.cpp
#include "Event.h"
#include "ClockCalendar.h"

Event::Event() : controllerID(ID_DEFAULT), payload("") {}

Event::Event(ControllerID controllerID, const String& timestamp, const String& payload)
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

String Event::getPayload() const {
    return payload;
}

void Event::setPayload(const char* newPayload) {
    payload = newPayload;
}
