// GpsModule.cpp
#include "GpsModule.h"
#include "EventManager.h"
#include "ClockCalendar.h"
#include <Arduino.h>

GpsModule::GpsModule(std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar)
    : eventManager(eventManager), clockCalendar(clockCalendar) {}

void GpsModule::captureInformationGPS() {
    Serial.println("capturePeriodicGPS:");

    Event gpsEvent(ID_GPS, clockCalendar->currentTime(), "GPS");
    Serial.println("XXXXXXXXXX - Add fila do GPS:");
    eventManager->addEvent(gpsEvent);
}

void GpsModule::getQueueGPSinternal() {
    Serial.println("checkQueueGPSinternal:");
    eventManager->printAllEvents();
}

GpsModule::~GpsModule() {
    // Implementação do destrutor, se necessário
}
