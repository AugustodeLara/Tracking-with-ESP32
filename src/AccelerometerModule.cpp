// AccelerometerModule.cpp
#include "AccelerometerModule.h"
#include "EventManager.h"
#include "ClockCalendar.h"
#include <Arduino.h>

AccelerometerModule::AccelerometerModule(std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar)
    : eventManager(eventManager), clockCalendar(clockCalendar) {}

void AccelerometerModule::captureInformationAccelerometer() {
    Serial.println("captureInformationAccelerometer:");

    //TODO: Integrate data to send in payload
    Event accelerometerEvent(ID_ACCELEROMETER, clockCalendar->getTimeNow(), "Accelerometer data");
    Serial.println("XXXXXXXXXX - Add fila do Acelerômetro:");
    eventManager->addEvent(accelerometerEvent);
}

void AccelerometerModule::anomalyDetection() {
    Serial.println("anomalyDetection:");
    //TODO: Include Model TinyMl 
   
}


AccelerometerModule::~AccelerometerModule() {
}
