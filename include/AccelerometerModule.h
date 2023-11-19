// AccelerometerModule.h
#ifndef ACCELEROMETERMODULE_H
#define ACCELEROMETERMODULE_H

#include <iostream>
#include <memory>
#include "Event.h"
#include "ClockCalendar.h"

class EventManager;

class AccelerometerModule {
public:
    AccelerometerModule(std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar);
    ~AccelerometerModule(); 

    void captureInformationAccelerometer(); 
    void anomalyDetection(); 
private:
    time_t lastUpdateTime;
    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<ClockCalendar> clockCalendar;
};

#endif // ACCELEROMETERMODULE_H
