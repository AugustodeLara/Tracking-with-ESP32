#include <Arduino.h>
#include <TimeLib.h>
#include "EventManager.h"
#include <TinyGPSPlus.h>
#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"


TinyGPSPlus gps;
LSM6DS3 myIMU; //Default constructor is I2C, addr 0x6B


static const int RXPin = 16, TXPin = 17;



#define RXD2 16
#define TXD2 17


time_t externalTime = 0; // Variável global para armazenar a hora externa

time_t getExternalTimeProvider() {
  return externalTime;
}

EventManager eventManager; // Crie um objeto da classe EventManager


void sendEventsToHost() {
  while (!eventManager.isEmpty()) {
    Event event = eventManager.getEvent();
    eventManager.removeEvent();
    Serial.print("APAGANDO");
    Serial.print("ID do Controlador: ");
    Serial.print(event.controllerID);
    Serial.print(", Data/Hora: ");
    Serial.print(hour(event.timestamp));
    Serial.print(":");
    Serial.print(minute(event.timestamp));
    Serial.print(":");
    Serial.println(second(event.timestamp));
  }
}



void displayInfo() {
  Serial.print(F("Location: "));
  if (gps.location.isValid()){
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print("Lng: ");
    Serial.print(gps.location.lng(), 6);
    Serial.println();

  } else {
    Serial.print(F("INVALID"));
  }
}


void updateSerial(){
  delay(500);
  while (Serial.available()) {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }

  while (Serial2.available()) {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }

}


void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  delay(3000);
  setSyncProvider(getExternalTimeProvider);
  setSyncInterval(60);
  myIMU.begin();

}

void loop() {


  /*
  Codigo para validar GPS
  if (Serial2.available())
   {
      Serial.print(char(Serial2.read()));
     // displayInfo();
    //  delay(2000);
   }
   */

  
  int controllerID = 1;
  time_t currentTime = now();

  Event newEvent;
  newEvent.controllerID = controllerID;
  newEvent.timestamp = currentTime;
  eventManager.addEvent(newEvent);

    Serial.print("ID do Controlador: ");
    Serial.print(newEvent.controllerID);
    Serial.print(", Data/Hora: ");
    Serial.print(hour(newEvent.timestamp));
    Serial.print(":");
    Serial.print(minute(newEvent.timestamp));
    Serial.print(":");
    Serial.println(second(newEvent.timestamp));

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == "receber") {
      sendEventsToHost();
    }
  }

  delay(2000);
  
}



int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}