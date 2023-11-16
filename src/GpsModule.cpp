#include "GpsModule.h"
#include "EventManager.h"

GpsModule::GpsModule(EventManager* eventManager) : eventManager(eventManager) {
    lastUpdateTime = now();
}

void GpsModule::captureInformationGPS() {
    Serial.println("capturePeriodicGPS:");

    Event gpsEvent;
    gpsEvent.setTimestamp(now());
    gpsEvent.setControllerID(2);
    gpsEvent.setPayload("GPS");

    Serial.println("Add fila do GPS:");
    eventManager->addEvent(gpsEvent);  // Adiciona o evento ao EventManager
}


LinkedList<Event> GpsModule::checkQueueGPSinternal() {
    LinkedList<Event> tempQueue;
    Serial.println("checkQueueGPSinternal:");
    eventManager->printAllEvents();
    return tempQueue;
}
