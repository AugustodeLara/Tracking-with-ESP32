// GpsModule.cpp
#include "GpsModule.h"
#include "EventManager.h"
#include "ClockCalendar.h"
#include <Arduino.h>

GpsModule::GpsModule(std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar)
    : eventManager(eventManager), clockCalendar(clockCalendar) {}


void GpsModule::captureInformationGPS(TinyGPSPlus& gps) {
    Serial.println("captureInformationGPS:");

    String locationInfo = "INVALID";

    while (Serial2.available() > 0) {
        if (gps.encode(Serial2.read())) {
            if (gps.location.isValid()) {
                locationInfo = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
                Serial.println("Location: " + locationInfo);
            } else {
                Serial.print(F("INVALID"));
            }

            if (millis() > 5000 && gps.charsProcessed() < 10) {
                Serial.println(F("No GPS detected: check wiring."));
                while(true);
            }

            
        }
    }
    Event gpsEvent(ID_GPS, clockCalendar->getTimeNow(), locationInfo.c_str());
    Serial.println("Add fila do GPS:");
    eventManager->addEvent(gpsEvent);
}



void GpsModule::getQueueGPSinternal() {
    Serial.println("checkQueueGPSinternal:");
    eventManager->printAllEvents();
}

GpsModule::~GpsModule() {
}
