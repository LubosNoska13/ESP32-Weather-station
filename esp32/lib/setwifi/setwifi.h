#ifndef SETWIFI_H
#define SETWIFI_H

#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

/*
    Class for connecting our ESP32 to internet
    WIFI
*/

class WifiConnection {
    private:
        // Wifi credentails imported from config.h file
        const char* const SSID = ssid;
        const char* const PASSWORD = password;
    public:
        // Method that needs to be called at startup
        void setup();
        // Method to scan all wifi networks
        void scan_network();
        // Method to connect to wifi
        void connect();
};

#endif // SETWIFI_H
