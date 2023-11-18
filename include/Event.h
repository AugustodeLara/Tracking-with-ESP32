// Event.h
#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>  // Adicionada a inclusão da biblioteca Arduino para String

class ClockCalendar;  // Forward declaration

enum ControllerID {
    ID_DEFAULT = 0,
    ID_ACCELEROMETER = 1,
    ID_GPS = 2,
    ID_LORA = 3,
    ID_WIFI = 4,
};

class Event {
public:
    Event();
    Event(ControllerID controllerID, const String& timestamp, const char* payload);

    ControllerID getControllerID() const;
    void setControllerID(ControllerID newControllerID);

    String getTimestamp() const;
    void setTimestamp(const String& newTimestamp);

    const char* getPayload() const;
    void setPayload(const char* newPayload);

private:
    ControllerID controllerID;
    String timestamp;
    const char* payload;
};

#endif  // EVENT_H
