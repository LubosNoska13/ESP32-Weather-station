#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

// Mqtt connection
void mqtt_connection(const char* const mqttServer, const int mqttPort, const char* const mqttUser, const char* const mqttPassword){
    client.setServer(mqttServer, mqttPort);
    while (!client.connected()) {
        Serial.println("Connecting to MQTT broker...");
        if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
        Serial.println("Connected to MQTT broker.");
        } else {
        Serial.print("Failed to connect to MQTT broker, rc=");
        Serial.print(client.state());
        Serial.println(" retrying in 5 seconds");
        delay(5000);
        }
    }
}

#endif
