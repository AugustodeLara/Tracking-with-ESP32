#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <iostream>
#include <memory>
#include "Event.h"
#include <TimeLib.h>

class EventManager; 

class GpsModule {
public:
    GpsModule(std::shared_ptr<EventManager> eventManager);
    ~GpsModule();

    void captureInformationGPS();
    void getQueueGPSinternal();

private:
    time_t lastUpdateTime;
    std::shared_ptr<EventManager> eventManager;
};

#endif // GPSMODULE_H
