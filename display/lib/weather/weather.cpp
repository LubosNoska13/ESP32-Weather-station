#include <Arduino.h>
#include "config.h"
#include "weather.h"
#include "big_font.h"
#include "small_font.h"
#include "icons.h"
#include "colors.h"
#include <ArduinoJson.h>

RectSize measureTextSize(String text) {
	int16_t x, y;
	uint16_t w, h;

	// Get the bounding box of the text
	display.getTextBounds(text, 0, 0, &x, &y, &w, &h);

	// Create a RectSize structure to store the width and height
	RectSize textSize;
	textSize.width = w;
	textSize.height = h;

	return textSize;
}

void displayText(String text, int color, int size, int x, int y) {
	display.setCursor(x,y);
	display.setTextColor(color);
	display.setTextSize(size);
	display.print(text);
}

void displayTextTemp(const float value, int color, int size, int x, int y) {
	display.setCursor(x,y);
	display.setTextColor(color);
	display.setTextSize(size);
	display.printf("%.1f C", value);
}

void displayTextPercent(const uint8_t value, int color, int size, int x, int y) {
	display.setCursor(x,y);
	display.setTextColor(color);
	display.setTextSize(size);
	display.printf("%d %", value);
}

void chooseWeatherIcon(int weather_type, bool is_max, const unsigned char** output_icon, char* output_text) {
	switch(weather_type) {
		case 1000:
			*output_icon = is_max == true ? weather_sunny_max : weather_sunny_mini;
			strcpy(output_text, "Sunny");
			break;

		case 1003:
			*output_icon = is_max == true ? weather_partly_cloudy_max : weather_partly_cloudy_mini;
			strcpy(output_text, "Cloudy");
			break;

		case 1006 ... 1009:
		case 1150 ... 1171:
		case 1180 ... 1183:
		case 1198:
		case 1204 ... 1210:
			*output_icon = is_max == true ? weather_clouds_max : weather_clouds_mini;
			strcpy(output_text, "Cloudy");
			break;
		
		case 1030:
		case 1135 ... 1147:
		case 1201:
			*output_icon = is_max == true ? weather_fog_max : weather_fog_mini;
			strcpy(output_text, "Foggy");
			break;

		case 1063 ... 1069:
		case 1186 ... 1195:
		case 1240 ... 1252:
			*output_icon = is_max == true ? weather_rain_max : weather_rain_mini;
			strcpy(output_text, "Rainy");
			break;	

		case 1072:
			*output_icon = is_max == true ? weather_freezing_max : weather_freezing_mini;
			strcpy(output_text, "Freezing");
			break;

		case 1114 ... 1117:
		case 1213 ... 1237:
		case 1255 ... 1264:
			*output_icon = is_max == true ? weather_snow_heavy_max : weather_snow_heavy_mini;
			strcpy(output_text, "Snowy");
			break;

		case 1087:
		case 1273 ... 1282:
			*output_icon = is_max == true ? weather_thunderstorm_max : weather_thunderstorm_mini;
			strcpy(output_text, "Thunderstorm");
			break;
	}
}

void displayMoonIcon(const char* moon_phase) {
	const int y = 255;
	if (strcmp(moon_phase, "Full Moon") == 0) {
		display.drawBitmap((display.width() / 2) - (55 / 2), y, moon_full, 55, 55, main_color);
	}
	else if (strcmp(moon_phase, "Waxing Gibbous") == 0) {
		display.drawBitmap((display.width() / 2) - (55 / 2), y, moon_waxing_gibbous, 55, 55, main_color);
	}
	else if (strcmp(moon_phase, "First Quarter") == 0) {
		display.drawBitmap((display.width() / 2) - (55 / 2), y, moon_first_quarter, 55, 55, main_color);
	}
	else if (strcmp(moon_phase, "Waxing Crescent") == 0) {
		display.drawBitmap((display.width() / 2) - (55 / 2), y, moon_waxing_crescent, 55, 55, main_color);
	}
	else if (strcmp(moon_phase, "New Moon") == 0) {
		display.drawBitmap((display.width() / 2) - (55 / 2), y, moon_new, 55, 55, main_color);
	}
	else if (strcmp(moon_phase, "Waning Crescent") == 0) {
		display.drawBitmap((display.width() / 2) - (55 / 2), y, moon_waning_crescent, 55, 55, main_color);
	}
	else if (strcmp(moon_phase, "Last Quarter") == 0) {
		display.drawBitmap((display.width() / 2) - (55 / 2), y, moon_last_quarter, 55, 55, main_color);
	}
	else if (strcmp(moon_phase, "Waning Gibbous") == 0) {
		display.drawBitmap((display.width() / 2) - (55 / 2), y, moon_waning_gibbous, 55, 55, main_color);
	}
}

void displayWeatherIcons(weather_data_t* weather_data_arr) {
	const uint8_t FORECAST_MENU_ICONS = 3;
	const unsigned char* icon;
	char description[10];

	// Left-side
	display.setFont(&small_font);

	for (uint8_t i = 0; i < FORECAST_MENU_ICONS; i++) {
		displayText(weather_data_arr[i].date, main_color, 1, (display.width() * (i + 1) / 4) - (measureTextSize(weather_data_arr[i].date).width / 2), 160);
		displayTextTemp(weather_data_arr[i].temp, white, 1, (display.width() * (i + 1) / 4) - (measureTextSize((String) weather_data_arr[i].temp).width / 2), 175);
		chooseWeatherIcon(weather_data_arr[i].type, false, &icon, description);
		display.drawBitmap((display.width() * (i + 1) / 4) - (45 / 2), 185, icon, 45, 45, main_color);
		displayTextPercent(weather_data_arr[i].chance_of_rain, main_color, 1, (display.width() * (i + 1) / 4) - (measureTextSize((String) weather_data_arr[i].chance_of_rain).width / 2), 245);
	}
}

void displayWeatherIconMax(weather_data_t* current_weather, const char* city) {
	const unsigned char* icon;
	char description[10];

	display.setFont(&big_font);
	displayTextTemp(current_weather->temp, white, 1, 120, 115);
	chooseWeatherIcon(current_weather->type, true, &icon, description);
	display.drawBitmap(25, 65, icon, 75, 75, main_color);
	display.setFont(&small_font);
	displayText(city, main_color, 1, 170, 80);
	displayText(description, main_color, 1, 170, 130);
}

String dayOfWeekToString(uint8_t dayOfWeek) {
	switch (dayOfWeek) {
		case 0: return "SUN";
		case 1: return "MON";
		case 2: return "TUE";
		case 3: return "WED";
		case 4: return "THU";
		case 5: return "FRI";
		case 6: return "SAT";
		default: return "";
	}
}

String monthToString(uint8_t month) {
	switch (month) {
		case 1: return "JAN";
		case 2: return "FEB";
		case 3: return "MAR";
		case 4: return "APR";
		case 5: return "MAY";
		case 6: return "JUN";
		case 7: return "JUL";
		case 8: return "AUG";
		case 9: return "SEP";
		case 10: return "OCT";
		case 11: return "NOV";
		case 12: return "DEC";
		default: return "";
	}
}

void get_forecast_data(HTTPClient* http, RTC_DS3231 rtc) {
	http->begin(weather_url + "key=" + weather_api_key + "&q=" + lat + ",%20" + lon + "&days=" + forecast_days + "&aqi=no&alerts=no&hour=6&tides=no");
	int httpCode = http->GET();

	if (httpCode == 200) {
		String JSON_Data = http->getString();
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

void displayUI(weather_data_t* current_weather, weather_data_t* weather_data_arr, const char* city, RTC_DS3231* rtc) {
	// Time and Date
	DateTime now = rtc->now();  	
	char clock[7] = "hh:mm";
    rtc->now().toString(clock);

  	// Format the date into a single String variable
  	String formattedDate = dayOfWeekToString(now.dayOfTheWeek()) + " " + monthToString(now.month()) + " " +
                        					 String(now.day(), DEC) + " " + String(now.year(), DEC);

	display.setFont(&small_font);
	displayText(formattedDate, main_color, 1, (display.width() - measureTextSize(formattedDate).width) / 2, 15);
	display.setFont(&big_font);
	displayText(clock, white, 1, (display.width() - measureTextSize(clock).width) / 2, 50);

	// City and Temperature
	displayWeatherIconMax(current_weather, city);
	displayWeatherIcons(weather_data_arr);
	displayMoonIcon(weather_data_arr[0].moon_phase);
	
	display.setFont(&small_font);
	// displayText("RAINY", main_color, 1, (display.width() * 3/4) - (measureTextSize("RAINY").width / 2), 250);
	// displayText("Precipitation: 50%", white, 1, (display.width() * 3/4) - (measureTextSize("Precipitation: 50%").width / 2), 262);
	// displayText("Humidity:  94%", white, 1, (display.width() * 3/4) - (measureTextSize("Humidity:  94%").width / 2), 274);

	displayText("Today", main_color, 1, (display.width() / 4) - (measureTextSize("Today").width / 2), 270);
	displayText(current_weather->sunrise, white, 1, (display.width() / 4) - (measureTextSize(current_weather->sunrise).width / 2), 290);
	displayText(current_weather->moonrise, white, 1, (display.width() / 4) - (measureTextSize(current_weather->moonrise).width / 2), 305);
}