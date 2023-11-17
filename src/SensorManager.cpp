#include "SensorManager.h"

SensorManager::SensorManager(std::shared_ptr<GpsModule> gpsModule, std::shared_ptr<EventManager> eventManager)
    : gpsModule(gpsModule), eventManager(eventManager), clockCalendar(1, 1, 2023, 12, 0, 0, 0) {
    accelerometerModule = std::make_shared<AccelerometerModule>();
    lastEmptyEventTime = now();
    lastGPSTime = now();
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
    clockCalendar.advance();  // Avance o relógio/calendário

    int currentHour, currentMinute, currentSecond, isPM;
    clockCalendar.readClock(currentHour, currentMinute, currentSecond, isPM);

    Serial.print("Tempo atual capture: ");
    Serial.print(currentHour);
    Serial.print(":");
    Serial.print(currentMinute);
    Serial.print(":");
    Serial.print(currentSecond);
    Serial.print(" ");
    Serial.println(isPM ? "PM" : "AM");

    // Calcula a diferença de tempo em segundos desde a última captura de GPS
int timeDifference = clockCalendar.calculateTimeDifference(ClockCalendar(1, 1, 2023, 12, 0, 0, 0));
    lastGPSTime = clockCalendar.getMillis();

    // Verifica se passaram pelo menos 10 segundos desde a última captura de GPS
    if (timeDifference >= 10) {
        Serial.println("Atingiu pelo menos 10 segundos:");

        // Captura informações GPS e adiciona à fila
        gpsModule->captureInformationGPS();
        lastGPSTime = clockCalendar.getMillis();;  // Atualiza o último tempo de captura
    } else {
        Serial.println("Tempo ainda não atingiu 10 segundos.");
    }

}

void SensorManager::emptyEventManagerQueue() {
    clockCalendar.advance();  // Avance o relógio/calendário

    int currentHour, currentMinute, currentSecond, isPM;
    clockCalendar.readClock(currentHour, currentMinute, currentSecond, isPM);

    unsigned long currentTime = millis();
    Serial.print("Tempo atual empty: ");
    Serial.print(currentHour);
    Serial.print(":");
    Serial.print(currentMinute);
    Serial.print(":");
    Serial.print(currentSecond);
    Serial.print(" ");
    Serial.println(isPM ? "PM" : "AM");

    // Verifica se passaram 90 segundos desde o último esvaziamento da fila do EventManager
    if (currentHour == 0 && currentMinute == 0 && (currentTime - lastEmptyEventTime) >= 90000) {
        lastEmptyEventTime = currentTime;
        Serial.println("Esvaziando a fila do EventManager.");
        while (!eventManager->isEmpty()) {
            eventManager->removeEvent();
        }
    } else {
        Serial.println("Empty Tempo ainda não atingiu 90 segundos.");
    }
}
