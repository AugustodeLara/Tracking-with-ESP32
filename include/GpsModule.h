#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <iostream>
#include "Event.h"
#include <LinkedList.h>
#include <TimeLib.h>


class GpsModule {
public:
    GpsModule();  // Construtor
    ~GpsModule(); // Destrutor

    // precisar ter uma função para quando receber um evento 
    // deve chamar essa função quando necessario = sendInformation
    // ela ira enviar estar informações [ID]+[DATAHORA]+[PAYLOAD]
    // deve ficar monitorando quando se tem anomalias
    
    void sendInformationGPS();
    // envia para a fila interna do GpsModule

    void testQueueGPS();

    LinkedList<Event> checkQueueGPSinternal();  // Verifica a fila do GpsModule e retorna a fila completa
    // olha a fila do GpsModule e transfere caso haja para a fila do SensorManager

    
    // Adicione aqui as declarações dos métodos públicos da classe
    // ter uma fila aqui?
    // e cada X tempo o SensorManager olhar a fila e passar para a fila de eventos gerais?

private:
    // Adicione aqui os membros privados da classe, se necessário
    LinkedList<Event> gpsQueue;  // Fila de eventos GPS
    time_t lastUpdateTime;  // Último tempo de atualização
};

#endif // GPSMODULE_H
