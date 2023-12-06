// main.cpp
#include "EventManager.h"
#include "SensorManager.h"
#include "GpsModule.h"
#include "AccelerometerModule.h"
#include "Event.h"
#include "WifiModule.h"
#include <TinyGPS++.h>
#include <Arduino_LSM6DS3.h>
#include "Wire.h"
#include "SPI.h"

const char* ssid = "2G_FLAVIA.E.ANDRE";
const char* password = "IlhaSC2021";

TinyGPSPlus gps;

#define RXD2 16
#define TXD2 17


std::shared_ptr<ClockCalendar> clockCalendar = std::make_shared<ClockCalendar>();
std::shared_ptr<WifiModule> wifiModule = std::make_shared<WifiModule>();
std::shared_ptr<EventManager> eventManager = std::make_shared<EventManager>(clockCalendar);
std::shared_ptr<GpsModule> gpsModule = std::make_shared<GpsModule>(eventManager, clockCalendar);
std::shared_ptr<AccelerometerModule> accelerometerModule = std::make_shared<AccelerometerModule>(eventManager, clockCalendar);
std::shared_ptr<SensorManager> sensorManager = std::make_shared<SensorManager>(gpsModule, accelerometerModule, eventManager, clockCalendar,wifiModule);


void setup() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);
  delay(500);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  clockCalendar->currentTime();
  clockCalendar->advance();

  sensorManager->checkQueueSensor();
  delay(600);
  
  sensorManager->PeriodicGPS(gps);
  delay(600);

  sensorManager->PeriodicAccelerometer();
  delay(600);

  gpsModule->getQueueGPSinternal();
  delay(600);

  sensorManager->emptyEventManagerQueue();
  delay(600);
}

int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}
