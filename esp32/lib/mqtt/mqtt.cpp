#include "mqtt.h"

// MQTT connection
void MqttConnection::connect() {
    client.setServer(MQTT_SERVER, MQTT_PORT);

    while (!client.connected()) {
        Serial.println("Connecting to MQTT broker...");
        if (client.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("Connected to MQTT broker.");
        } else {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
}
