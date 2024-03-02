#include "setwifi.h"

void WifiConnection::setup() {
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect(true);          // Disconnect from any previously connected network
}

void WifiConnection::scan_network() {
    debug("Scanning for Wi-Fi networks...");
    int networkCount = WiFi.scanNetworks();
    if (networkCount == 0) {
        debug("No networks found.");
    } else {
        debug(networkCount);
        debug(" networks found.");
        for (int i = 0; i < networkCount; ++i) {
            debug("Network name: ");
            debug(WiFi.SSID(i));
        }
    }
}

void WifiConnection::connect() {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        debug("Connecting to WiFi...");
    }
    debug("Connected to WiFi");
}