// GPSModule.h
#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <iostream>
#include <memory>
#include "Event.h"
#include "ClockCalendar.h"
#include <TinyGPS++.h>  

class EventManager; 

class GpsModule {
public:
    GpsModule(std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar);
    ~GpsModule();

    void captureInformationGPS(TinyGPSPlus& gps);
    void getQueueGPSinternal();
    void displayInfo();
    bool eventAlreadyAdded(const String& location) const;

private:
    time_t lastUpdateTime;
    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<ClockCalendar> clockCalendar;
};

#endif // GPSMODULE_H
