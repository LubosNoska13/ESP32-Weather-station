#ifndef SETWIFI_H
#define SETWIFI_H

#include <Arduino.h>
#include <WiFi.h>

void wifi_setup();
void scan_network();
void connect_to_wifi(const char* const ssid, const char* const password);

#endif
