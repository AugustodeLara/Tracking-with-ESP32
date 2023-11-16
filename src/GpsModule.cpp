#include "GpsModule.h"

GpsModule::GpsModule() {
    // Implemente o código do construtor, se necessário
    lastUpdateTime = now();
  //  testQueueGPS();
    
}

GpsModule::~GpsModule() {
    // Implemente o código do destrutor, se necessário
}

// Implemente aqui os métodos públicos da classe


void GpsModule::sendInformationGPS() {
    // Cria um evento e o adiciona à fila interna
    Event gpsEvent;
    gpsEvent.setTimestamp(now());
    gpsEvent.setControllerID(2);
    gpsEvent.setPayload("GPS");

    // Adicione outras informações do GPS à carga útil, se necessário
    Serial.println("Add fila do GPS:");

    gpsQueue.add(gpsEvent);
}

void GpsModule::testQueueGPS() {
    // Adiciona um novo elemento à fila a cada 30 segundos
    if (now() - lastUpdateTime >= 2) {
        sendInformationGPS();
        delay(1000);
        lastUpdateTime = now();
    }
}


LinkedList<Event> GpsModule::checkQueueGPSinternal() {
    LinkedList<Event> tempQueue;
    
    // Verifica a fila de eventos GPS e transfere para a fila temporária
    while (!gpsQueue.size() == 0) {
        Event gpsEvent = gpsQueue.remove(0);
        tempQueue.add(gpsEvent);
    }

    // Imprime os elementos da fila na tela
    Serial.println("Elementos na fila do GPS intenal:");
        for (int i = 0; i < tempQueue.size(); ++i) {
            Event event = tempQueue.get(i);
            Serial.print("ID do Controlador: ");
            Serial.print(event.getControllerID());
            Serial.print(", Data/Hora: ");
            Serial.print(hour(event.getTimestamp()));
            Serial.print(":");
            Serial.print(minute(event.getTimestamp()));
            Serial.print(":");
            Serial.println(second(event.getTimestamp()));
        }
        Serial.println("End GPS intenal");

    // Retorna a fila completa
    return tempQueue;
}


