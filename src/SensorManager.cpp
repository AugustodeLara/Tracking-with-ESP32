// SensorManager.cpp
#include "SensorManager.h"

SensorManager::SensorManager(std::shared_ptr<GpsModule> gpsModule, std::shared_ptr<AccelerometerModule> accelerometerModule, std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar)
    : gpsModule(gpsModule), accelerometerModule(accelerometerModule), eventManager(eventManager), clockCalendar(clockCalendar) {
    lastEmptyEventTime = clockCalendar->getMillis();
    lastGPSTime = clockCalendar->getMillis();
    lastAccelerometerTime = clockCalendar->getMillis();
}

void SensorManager::checkQueueSensor() {
    Serial.println("checkQueueSensor:");
    eventManager->printAllEvents();
}


void SensorManager::PeriodicGPS(TinyGPSPlus& gps) {
    unsigned long currentTime = clockCalendar->getMillis();
    unsigned long timeDifference = currentTime - lastGPSTime;

    //Serial.print("XXX - lastGPSTime: ");
    Serial.println(lastGPSTime);

    //Serial.print("XXX - timeDifference: ");
    Serial.println(timeDifference);

      if (timeDifference >= 31500 || lastGPSTime == 0) {
        Serial.println("Atingiu pelo menos 10 segundos:");

        // Captura informações GPS e adiciona à fila
        gpsModule->captureInformationGPS(gps);  // Passe o objeto gps como argumento
        lastGPSTime = currentTime;  // Atualiza o último tempo de captura
    } else {
        Serial.println("Tempo ainda não atingiu 10 segundos.");
    }
}

void SensorManager::PeriodicAccelerometer() {
    unsigned long currentTime = clockCalendar->getMillis();
    unsigned long timeDifference = currentTime - lastAccelerometerTime;

    Serial.print("XXX - lastAccelerometerTime: ");
    Serial.println(lastAccelerometerTime);

    Serial.print("XXX - timeDifference accelerometer: ");
    Serial.println(timeDifference);

     if (timeDifference >= 21500 || lastGPSTime == 0) {
        Serial.println("Atingiu pelo menos 10 segundos:");

        // Captura informações do acelerômetro e adiciona à fila
        accelerometerModule->captureInformationAccelerometer();
        lastAccelerometerTime = currentTime;  // Atualiza o último tempo de captura
    } else {
        Serial.println("Tempo ainda não atingiu 10 segundos.");
    }
}

void SensorManager::emptyEventManagerQueue() {
    // Verifica se passaram 90 segundos desde o último esvaziamento da fila do EventManager
    unsigned long currentTime = clockCalendar->getMillis();
    unsigned long timeDifference = currentTime - lastEmptyEventTime;

    Serial.print("XXX - lastEmptyEventTime: ");
    Serial.println(lastEmptyEventTime);

    Serial.print("XXX - timeDifference empty: ");
    Serial.println(timeDifference);

    if (timeDifference >= (31500*6) && eventManager->getSizeQueue() >= 6) { 
        lastEmptyEventTime = currentTime;
        Serial.println("Esvaziando a fila do EventManager.");
        while (!eventManager->isEmpty()) {
            eventManager->removeEvent();
        }
    } else {
        Serial.println("Empty Tempo ainda não atingiu regra de limpeza");
    }
}


SensorManager::~SensorManager() {
}