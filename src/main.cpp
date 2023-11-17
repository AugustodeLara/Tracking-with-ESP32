#include <Arduino.h>
#include <TimeLib.h>
#include "EventManager.h"
#include "SensorManager.h"
#include "GpsModule.h"
#include "Event.h"
#include <TinyGPSPlus.h>
#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"


EventManager * eventManager = new EventManager();
GpsModule* gpsModule = new GpsModule(eventManager);
SensorManager* sensorManager = new SensorManager(gpsModule,eventManager);


void setup() {
  Serial.begin(115200);
  delay(500);
}

void loop() {
 /* 
 Serial.println("loop");
  if (Serial.available() > 0) {
        char incomingChar = Serial.read();
         Serial.println("Serial.available():");

        if (incomingChar == 'A') {
                   Serial.println("incomingChar A");

            // Aguarda o próximo caractere
            while (Serial.available() == 0);

            incomingChar = Serial.read();

            if (incomingChar == 'D') {
                   Serial.println("incomingChar D");

                // Aguarda o próximo caractere
                while (Serial.available() == 0);

                incomingChar = Serial.read();

                if (incomingChar == 'M') {
                                     Serial.println("incomingChar M");

                    // Recebeu a mensagem completa 'ADM', então envie a fila de eventos
                    //sendEventQueue();
                }
            }
        }
    }

    delay(2000);
}
*/

delay(1000);
sensorManager->checkQueueSensor();
delay(1000);
sensorManager->PeriodicGPS();  
delay(1000);
gpsModule->captureInformationGPS();
delay(1000);
gpsModule->checkQueueGPSinternal();
delay(1000);
sensorManager->emptyEventManagerQueue();

}


int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}
