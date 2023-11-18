//#include <Arduino.h>
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

//devo ter aqui a criação do meu tempo, e ele deve ser passado para o EventManager e para os outros que precisarem de tempo.
//std::shared_ptr<EventManager> eventManager = std::make_shared<EventManager>();

std::shared_ptr<ClockCalendar> clockCalendar = std::make_shared<ClockCalendar>();
std::shared_ptr<EventManager> eventManager = std::make_shared<EventManager>(clockCalendar);
std::shared_ptr<GpsModule> gpsModule = std::make_shared<GpsModule>(eventManager, clockCalendar);
std::shared_ptr<SensorManager> sensorManager = std::make_shared<SensorManager>(gpsModule, eventManager, clockCalendar);



void setup() {
  Serial.begin(115200);
  delay(500);
}

void loop() {
  
  String current_time = clockCalendar->currentTime();
  Serial.print("XXXXXXXXXXXXXXXXX - Tempo atual: ");
  Serial.println(current_time);
  clockCalendar->advance();

  sensorManager->checkQueueSensor();
  delay(800);
  sensorManager->PeriodicGPS();
  delay(800);
  // gpsModule->captureInformationGPS();
  // delay(1000);
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
