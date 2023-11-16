#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

class Event {
public:
    Event();
    Event(int controllerID, time_t timestamp, const char* payload);

    // Métodos públicos de acesso
    int getControllerID() const;
    void setControllerID(int newControllerID);

    time_t getTimestamp() const;
    void setTimestamp(time_t newTimestamp);

    const char* getPayload() const;
    void setPayload(const char* newPayload);

private:
    int controllerID;
    time_t timestamp;
    const char* payload;
};

#endif // EVENT_H
