// main.cpp
#include "EventManager.h"
#include "SensorManager.h"
#include "GpsModule.h"
#include "AccelerometerModule.h"
#include "Event.h"
#include <TinyGPS++.h>
#include <Arduino_LSM6DS3.h>
#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"

TinyGPSPlus gps;

#define RXD2 16
#define TXD2 17


// TODO: Move to CentralManager
std::shared_ptr<ClockCalendar> clockCalendar = std::make_shared<ClockCalendar>();
std::shared_ptr<EventManager> eventManager = std::make_shared<EventManager>(clockCalendar);
std::shared_ptr<GpsModule> gpsModule = std::make_shared<GpsModule>(eventManager, clockCalendar);
std::shared_ptr<AccelerometerModule> accelerometerModule = std::make_shared<AccelerometerModule>(eventManager, clockCalendar);
std::shared_ptr<SensorManager> sensorManager = std::make_shared<SensorManager>(gpsModule, accelerometerModule, eventManager, clockCalendar);

void setup() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);
  delay(500);
}

void loop() {
  clockCalendar->currentTime();
  clockCalendar->advance();

  sensorManager->checkQueueSensor();
  delay(800);
  
  sensorManager->PeriodicGPS(gps);
  delay(800);

  sensorManager->PeriodicAccelerometer();
  delay(800);

  gpsModule->getQueueGPSinternal();
  delay(800);

  sensorManager->emptyEventManagerQueue();
}

int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}
