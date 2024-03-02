#ifndef DISPLAY_H
#define DISPLAY_H

// #include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "RTClib.h"

static Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

struct RectSize {
	uint16_t width;
	uint16_t height;
};

typedef struct {
	float temp;
	char date[5];
	int type;
	char moon_phase[20];
	char sunrise[10];
	char moonrise[10];
	uint8_t chance_of_rain;
} weather_data_t;

RectSize measureTextSize(String text);

void displayText(String text, int color, int size, int x, int y);

void displayTextTemp(const float value, int color, int size, int x, int y);

void chooseWeatherIcon(int weather_type, bool is_max, const unsigned char** output_icon, const char* output_text);

void displayWeatherIcons(int weather_type, weather_data_t* weather_data_arr);

void displayWeatherIconMax(weather_data_t* current_weather, const char* city);

void displayMoonIcon(const char* moon_phase);

void displayUI(weather_data_t* current_weather, weather_data_t* weather_data_arr, const char* city, RTC_DS3231 rtc);

#endif
