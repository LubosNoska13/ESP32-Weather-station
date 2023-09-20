#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <WiFi.h>
#include "config.h"

/*
    Class for connecting our ESP32 with MQTT server.
    MQTT
*/

class MqttConnection {
    private:
        // All the essential credentails for mqtt connection
        const char* const MQTT_SERVER = mqttServer;
        const int MQTT_PORT = mqttPort;
        const char* const MQTT_USER = mqttUser;
        const char* const MQTT_PASSWORD = mqttPassword;
        WiFiClient espClient;
    public:
        PubSubClient client;
        MqttConnection() : client(espClient) {}
        // Method to connect ESP32 with mqtt server.
        void connect();
};

#endif // MQTT_H
