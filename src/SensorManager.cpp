#include "SensorManager.h"

SensorManager::SensorManager(std::shared_ptr<GpsModule> gpsModule, std::shared_ptr<EventManager> eventManager, std::shared_ptr<ClockCalendar> clockCalendar)
    : gpsModule(gpsModule), eventManager(eventManager), clockCalendar(clockCalendar) {
    accelerometerModule = std::make_shared<AccelerometerModule>();
    lastEmptyEventTime = clockCalendar->getMillis();  
    lastGPSTime = clockCalendar->getMillis();         // Use millis() instead of now()
}

SensorManager::~SensorManager() {
    // O destrutor do std::shared_ptr faz o trabalho de liberar a memória automaticamente.
}

void SensorManager::checkQueueSensor() {
    Serial.println("checkQueueSensor:");
    eventManager->printAllEvents();
}

void SensorManager::checkQueueAccelerometer() {
    // Implemente a lógica para consultar a fila do AccelerometerModule, se necessário
    // Adicione eventos à fila interna do SensorManager conforme necessário
}

void SensorManager::PeriodicGPS() {

    String current_time = clockCalendar->currentTime();
    Serial.print("XXXXXXXXXXXXXXXXX - Tempo atual PERI: ");
    Serial.println(current_time);

    // Verifica se passaram pelo menos 10 segundos desde a última captura de GPS
    unsigned long currentTime = clockCalendar->getMillis();
    unsigned long timeDifference = currentTime - lastGPSTime;

    Serial.print("XXX - lastGPSTime: ");
    Serial.println(lastGPSTime);

    Serial.print("XXX - timeDifference: ");
    Serial.println(timeDifference);

    // Verifica se passaram pelo menos 10 segundos desde a última captura de GPS
    if (timeDifference >= 31500 || lastGPSTime == 0) {
        Serial.println("Atingiu pelo menos 10 segundos:");

        // Captura informações GPS e adiciona à fila
        gpsModule->captureInformationGPS();
        lastGPSTime = currentTime;  // Atualiza o último tempo de captura
    } else {
        Serial.println("Tempo ainda não atingiu 10 segundos.");
    }
}


void SensorManager::emptyEventManagerQueue() {
    // Verifica se passaram 90 segundos desde o último esvaziamento da fila do EventManager
    unsigned long currentTime = clockCalendar->getMillis();
    unsigned long timeDifference = currentTime - lastEmptyEventTime;

    String current_time = clockCalendar->currentTime();
    Serial.print("XXXXXXXXXXXXXXXXX - Tempo atual empty: ");
    Serial.println(current_time);

    Serial.print("XXX - lastEmptyEventTime: ");
    Serial.println(lastEmptyEventTime);

    Serial.print("XXX - timeDifference empty: ");
    Serial.println(timeDifference);

    if (timeDifference >= (31500*6) && eventManager->getSizeQueue() >=6) { 
        lastEmptyEventTime = currentTime;
        Serial.println("Esvaziando a fila do EventManager.");
        while (!eventManager->isEmpty()) {
            eventManager->removeEvent();
        }
    } else {
        Serial.println("Empty Tempo ainda não atingiu regra de limpeza");
    }
}
