#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <iostream>
#include <Arduino.h> 
#include "GpsModule.h"
#include "AccelerometerModule.h"
#include "EventManager.h"  // Inclua o cabeçalho completo do EventManager

class SensorManager {
public:
    SensorManager(GpsModule *gpsModule, EventManager* eventManager);  // Construtor
    ~SensorManager(); // Destrutor

    void checkQueueSensor();
    void checkQueueAccelerometer();
    void printInternalQueue();
    void PeriodicGPS();
    void emptyEventManagerQueue();

private:
    GpsModule* gpsModule;
    AccelerometerModule*  accelerometerModule;
    LinkedList<Event> internalQueue;
    EventManager* eventManager;  // Adicione um ponteiro para EventManager
    unsigned long lastGPSTime; 
    unsigned long lastEmptyEventTime;  



};

#endif // SENSORMANAGER_H
