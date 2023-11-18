// GPSModule.h
#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <iostream>
#include <memory>
#include "Event.h"
#include "ClockCalendar.h"  // Adicione esta linha

class EventManager; 

class GpsModule {
public:
    GpsModule(std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar);
    ~GpsModule();

    void captureInformationGPS();
    void getQueueGPSinternal();

private:
    time_t lastUpdateTime;
    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<ClockCalendar> clockCalendar;  // Alteração aqui para usar std::shared_ptr
};

#endif // GPSMODULE_H