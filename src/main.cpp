#include <Arduino.h>
#include <TimeLib.h>
#include <memory>
#include "EventManager.h"
#include "SensorManager.h"
#include "GpsModule.h"
#include "Event.h"
#include <TinyGPSPlus.h>
#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"

// Utilize std::shared_ptr para gerenciamento automático da memória
std::shared_ptr<EventManager> eventManager = std::make_shared<EventManager>();
std::shared_ptr<GpsModule> gpsModule = std::make_shared<GpsModule>(eventManager);
std::shared_ptr<SensorManager> sensorManager = std::make_shared<SensorManager>(gpsModule, eventManager);

void setup() {
  Serial.begin(115200);
  delay(500);
}

void loop() {
  sensorManager->checkQueueSensor();
  delay(1000);
  sensorManager->PeriodicGPS();
  delay(1000);
  // gpsModule->captureInformationGPS();
  // delay(1000);
  gpsModule->getQueueGPSinternal();
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
