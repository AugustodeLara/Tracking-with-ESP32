#include "WifiModule.h"

const char* serverAddress = "http://192.168.0.55/hello";

WifiModule::WifiModule() {

}

WifiModule::~WifiModule() {
}

void WifiModule::makeRequest() {
  HTTPClient http;

  // Use POST request to send JSON payload
  http.begin(serverAddress);
  http.addHeader("Content-Type", "application/json");

  // Define o payload JSON
  String payload = "{\"message\": \"TESTESTE!\"}";

  // Envia a solicitação POST com o payload
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode == 200) {
    Serial.println("HTTP Request was successful 200");
    String response = http.getString();
    Serial.println("Response payload: " + response);
  } else {
    Serial.println("HTTP Request failed");
    Serial.println("HTTP Response code: " + String(httpResponseCode));
  }

  // Libera os recursos
  http.end();
}