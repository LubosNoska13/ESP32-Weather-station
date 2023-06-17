#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <WiFi.h>

extern WiFiClient espClient;
extern PubSubClient client;

// MQTT connection
void mqtt_connection(const char* const mqttServer, const int mqttPort, const char* const mqttUser, const char* const mqttPassword);

#endif
