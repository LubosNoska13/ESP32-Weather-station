#ifndef CONFIG_H
#define CONFIG_H

// Wifi settings
static const char* const ssid = "";
static const char* const password = "";

// MQTT settings
static const char* const mqttServer = "";
static const int mqttPort = 1883;
static const char* const mqttUser = "";
static const char* const mqttPassword = "";
static const char* const mqttTopic = "esp32/data";

// General settings
static const char* const device = "ESP32";
const uint16_t frequency_of_reading_data = 10000ul;         // every 10 seconds 

#endif  // CONFIG_H
