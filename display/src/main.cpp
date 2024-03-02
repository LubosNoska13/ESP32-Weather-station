#include <Arduino.h>
#include <SPI.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "setwifi.h"
#include "config.h"
#include "weather.h"
#include "big_font.h"
#include "small_font.h"
#include "icons.h"
#include "colors.h"
#include <Wire.h>
#include "ntp.h"
#include "RTClib.h"

// Create instances
WifiConnection wifi;
HTTPClient http;
RTC_DS3231 rtc;
NTP ntp;

void setup() {
	Serial.begin(9600);

	delay(3000);
	
	//=== Initialize
	// I2C connection
	Wire.begin(21, 14);

	// Display
	display.begin();
	display.fillScreen(black);

	// Wifi
	wifi.setup();
	wifi.connect();

	// RTC
	if (! rtc.begin()) {
		debug("Couldn't find RTC");
		while (1) delay(10);
	}

	// NTP
	ntp.setup();
	ntp.set_date(&rtc);

	// HTTP
	http.begin(weather_url + "key=" + weather_api_key + "&q=" + lat + ",%20" + lon + "&days=" + forecast_days + "&aqi=no&alerts=no&hour=6&tides=no");
	int httpCode = http.GET();

	if (httpCode == 200) {
		String JSON_Data = http.getString();
		debug(JSON_Data);

		DynamicJsonDocument doc(6144);
		deserializeJson(doc, JSON_Data);
		JsonObject obj = doc.as<JsonObject>();

		weather_data_t current_weather;
		const char* city = obj["location"]["name"].as<const char*>();
		const float current_temp = obj["current"]["temp_c"].as<float>();
		const int current_weather_type = obj["current"]["condition"]["code"].as<int>();
		const char* sunrise = obj["forecast"]["forecastday"][0]["astro"]["sunrise"].as<const char*>();
		const char* moonrise = obj["forecast"]["forecastday"][0]["astro"]["moonrise"].as<const char*>();
		
		if (strcmp(moonrise, "No moonrise") == 0) {
			strcpy(current_weather.moonrise, "");
		} else {
			strcpy(current_weather.moonrise, moonrise);
		}

		current_weather.temp = current_temp;
		current_weather.type = current_weather_type;
		strcpy(current_weather.sunrise, sunrise);

		weather_data_t weather_data_arr[3];
		for (uint8_t i = 0; i < forecast_days; i++) {
			const long timestamp = obj["forecast"]["forecastday"][i]["date_epoch"].as<long>();
			const float avg_temp = obj["forecast"]["forecastday"][i]["day"]["avgtemp_c"].as<float>();
			const uint8_t chance_of_rain = obj["forecast"]["forecastday"][i]["day"]["daily_chance_of_rain"].as<uint8_t>();
			const int weather_type = obj["forecast"]["forecastday"][i]["day"]["condition"]["code"].as<int>();
			const char* moon_phase = obj["forecast"]["forecastday"][i]["astro"]["moon_phase"].as<const char*>();

			// Convert timestamp to day of the week
			struct tm *tm_info = gmtime(&timestamp);
			char date[5] = {};
			strftime(date, sizeof(date), "%a", tm_info);

			strcpy(weather_data_arr[i].date, date);
			weather_data_arr[i].temp = avg_temp;
			weather_data_arr[i].type = weather_type;
			weather_data_arr[i].chance_of_rain = chance_of_rain;
			strcpy(weather_data_arr[i].moon_phase, moon_phase);
		}
		displayUI(&current_weather, weather_data_arr, city, &rtc);
	}
}

void loop() {

}