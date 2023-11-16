#include "SensorManager.h"

SensorManager::SensorManager(GpsModule* gpsModule) : gpsModule(gpsModule)  {
    // Implemente o código do construtor, se necessário

    //checkQueueGPS();

    accelerometerModule = new AccelerometerModule();
}

SensorManager::~SensorManager() {
    // Implemente o código do destrutor, se necessário
    delete gpsModule;
    delete accelerometerModule;
}

void SensorManager::checkQueueGPS() {
    // Consulta a fila do GPSModule a cada 60 segundos
   // if (now() % 5 == 0) {
        // Chama a função checkQueueGPS do GPSModule
        LinkedList<Event> gpsQueue = gpsModule->checkQueueGPSinternal();

        // Adiciona os eventos da fila do GPS à fila interna do SensorManager
        while (!gpsQueue.size() == 0) {
            Event gpsEvent = gpsQueue.remove(0);
            internalQueue.add(gpsEvent);
        }
   // }
}

void SensorManager::checkQueueAccelerometer() {
    // Implemente a lógica para consultar a fila do AccelerometerModule, se necessário
    // Adicione eventos à fila interna do SensorManager conforme necessário
}

void SensorManager::printInternalQueue() {
    // Imprime as informações da fila interna a cada 15 segundos
    //if (now() % 5 == 0) {
        Serial.println("Printing Internal Queue:");
        for (int i = 0; i < internalQueue.size(); ++i) {
            Event event = internalQueue.get(i);
            Serial.print("ID do Controlador: ");
            Serial.print(event.getControllerID());
            Serial.print(", Data/Hora: ");
            Serial.print(hour(event.getTimestamp()));
            Serial.print(":");
            Serial.print(minute(event.getTimestamp()));
            Serial.print(":");
            Serial.println(second(event.getTimestamp()));
        }
        Serial.println("End of Internal Queue");
   // }
}
