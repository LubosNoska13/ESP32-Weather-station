#ifndef DISPLAY_H
#define DISPLAY_H

// #include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "RTClib.h"
#include <HTTPClient.h>

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

typedef struct {
	String date;
} today_t;

RectSize measureTextSize(String text);

void displayText(String text, int color, int size, int x, int y);

void displayTextTemp(const float value, int color, int size, int x, int y);

void chooseWeatherIcon(int weather_type, bool is_max, const unsigned char** output_icon, const char* output_text);

void displayForecastWeather(int weather_type, weather_data_t* weather_data_arr);

void displayCurrentWeather(weather_data_t* current_weather, const char* city);

void displayMoonIcon(const char* moon_phase);

String dayOfWeekToString(uint8_t dayOfWeek);

String monthToString(uint8_t month);

void get_forecast_data(HTTPClient* http);

void display_update_time_date(RTC_DS3231* rtc, bool update_date, today_t* today);

void update_date(today_t* today);

void displayUI(weather_data_t* current_weather, weather_data_t* weather_data_arr, const char* city);

#endif
