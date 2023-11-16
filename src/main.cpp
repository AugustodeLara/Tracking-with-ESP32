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

//sensorManager->checkQueueSensor();
//  delay(1000);
sensorManager->capturePeriodicGPS();  
delay(1000);
//gpsModule->captureInformationGPS();
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
