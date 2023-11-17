#include "GpsModule.h"
#include "EventManager.h"

GpsModule::GpsModule(std::shared_ptr<EventManager> eventManager) : eventManager(eventManager) {
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

void GpsModule::getQueueGPSinternal() {
    Serial.println("checkQueueGPSinternal:");
    eventManager->printAllEvents();
}

// Certifique-se de que o destrutor esteja implementado
GpsModule::~GpsModule() {
    // Implementação do destrutor, se necessário
}
