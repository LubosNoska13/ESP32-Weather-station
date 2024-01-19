#include "setwifi.h"

void WifiConnection::setup() {
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect(true);          // Disconnect from any previously connected network
}

void WifiConnection::scan_network() {
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

void WifiConnection::connect() {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}