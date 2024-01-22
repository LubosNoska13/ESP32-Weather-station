#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.println(x)
#else
#define debug(x)
#endif

// Wifi settings
static const char* const ssid = "";
static const char* const password = "";

// API 
static String weather_url = "";
static String const weather_api_key = "";

// Location
static String lat = "";
static String lon = "";

const uint8_t forecast_days = 3; 

// LCD Display pins
#define TFT_RST       4
#define TFT_DC        5
#define TFT_CS        34
#define TFT_MOSI      35
#define TFT_CLK       36
#define TFT_MISO      37

#define main_color    cyan

// General settings
static const char* const device = "ESP32-display";

#endif  // CONFIG_H