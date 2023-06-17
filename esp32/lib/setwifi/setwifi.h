#ifndef SETWIFI_H
#define SETWIFI_H

#include <Arduino.h>
#include <WiFi.h>


void wifi_setup(){
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect(true); // Disconnect from any previously connected network
}

void scan_network(){
    Serial.println("Scanning for Wi-Fi networks...");
    int networkCount = WiFi.scanNetworks();
    if (networkCount == 0) {
        Serial.println("No networks found.");
    } else {
        Serial.print(networkCount);
        Serial.println(" networks found.");
        for (int i = 0; i < networkCount; ++i) {
            Serial.print("Network name: ");
            Serial.println(WiFi.SSID(i));
        }
    }
}

void connect_to_wifi(const char* const ssid, const char* const password){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

#endif