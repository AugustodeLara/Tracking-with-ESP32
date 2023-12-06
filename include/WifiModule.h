#ifndef WIFIMODULE_H
#define WIFIMODULE_H

#include <iostream>
#include <HTTPClient.h>
#include <WiFi.h>

class WifiModule {
public:
    WifiModule(); 
    ~WifiModule(); 
    void makeRequest(); 
private:
};

#endif // WIFIMODULE_H
