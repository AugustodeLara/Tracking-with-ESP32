#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <iostream>
#include <Arduino.h> 
#include "GpsModule.h"
#include "AccelerometerModule.h"

class SensorManager {
public:
    SensorManager(GpsModule *gpsModule);  // Construtor
    ~SensorManager(); // Destrutor

    // Adicione aqui as declarações dos métodos públicos da classe

    void checkQueueGPS();
    // deve consultar a fila do GPS para verificar se há algo la dentro
    // deve fazer isso a cada 60 segundos
    // deve chamar a função checkQueueGPS e o retorno dela deve adicionar em uma outra fila esta fila sera interna do SensorManager

    void checkQueueAccelerometer();

    void printInternalQueue();  // Imprime as informações da fila interna


private:

    GpsModule* gpsModule;
    AccelerometerModule*  accelerometerModule;
    LinkedList<Event> internalQueue;  // Fila interna do SensorManager


};

#endif // SENSORMANAGER_H
