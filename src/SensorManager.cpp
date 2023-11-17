#include "SensorManager.h"

SensorManager::SensorManager(GpsModule* gpsModule, EventManager* eventManager) : gpsModule(gpsModule)  , eventManager(eventManager){
    // Implemente o código do construtor, se necessário

    //checkQueueGPS();
    accelerometerModule = new AccelerometerModule();
    lastEmptyEventTime = now();
    lastGPSTime = now();

}

SensorManager::~SensorManager() {
    // Implemente o código do destrutor, se necessário
    delete gpsModule;
    delete accelerometerModule;
}

void SensorManager::checkQueueSensor() {
        Serial.println("checkQueueSensor:");
       // eventManager->removeEvent();
        eventManager->printAllEvents();
}

void SensorManager::checkQueueAccelerometer() {
    // Implemente a lógica para consultar a fila do AccelerometerModule, se necessário
    // Adicione eventos à fila interna do SensorManager conforme necessário
}


void SensorManager::PeriodicGPS() {
    unsigned long currentTime = millis();
    Serial.print("Tempo atual capture: ");
    Serial.println(currentTime);

    // Verifica se passaram 10 segundos desde a última captura de GPS
    if (currentTime - lastGPSTime >= 10000) {
        Serial.println("Atingiu 10 segundos:");
        gpsModule->captureInformationGPS();
        lastGPSTime = currentTime;
    } else {
        Serial.println("Tempo ainda não atingiu 10 segundos.");
    }

}

void SensorManager::emptyEventManagerQueue() {
    unsigned long currentTime = millis();
    Serial.print("Tempo atual empty: ");
    Serial.println(currentTime);
    // Verifica se passaram 90 segundos desde o último esvaziamento da fila do EventManager
    if (currentTime - lastEmptyEventTime >= 90000) {
        lastEmptyEventTime = currentTime;
        Serial.println("Esvaziando a fila do EventManager.");
    while (!eventManager->isEmpty()) {
            eventManager->removeEvent();
    }
    } else {
        Serial.println("Empty Tempo ainda não atingiu 90 segundos.");
    }


    
}

