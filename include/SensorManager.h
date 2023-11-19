// SensorManager.h
#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <iostream>
#include <Arduino.h> 
#include "GpsModule.h"
#include "AccelerometerModule.h"
#include "EventManager.h"
#include "ClockCalendar.h"  

class SensorManager {
public:
    SensorManager(std::shared_ptr<GpsModule> gpsModule, std::shared_ptr<AccelerometerModule> accelerometerModule, std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar);
    ~SensorManager();

    void checkQueueSensor();
    void printInternalQueue();
    void PeriodicGPS(TinyGPSPlus& gps);
    void PeriodicAccelerometer();
    void emptyEventManagerQueue();

private:
    std::shared_ptr<GpsModule> gpsModule;
    std::shared_ptr<AccelerometerModule> accelerometerModule;
    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<ClockCalendar> clockCalendar;
    unsigned long lastGPSTime;
    unsigned long lastEmptyEventTime;
    unsigned long lastAccelerometerTime;
};

#endif // SENSORMANAGER_H
