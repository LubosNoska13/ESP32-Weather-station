#include <Arduino.h>
#include <SPI.h>
#include "setwifi.h"
#include "config.h"
#include "weather.h"
#include "big_font.h"
#include "small_font.h"
#include "icons.h"
#include "colors.h"
#include <Wire.h>
#include "ntp.h"
#include <HTTPClient.h>
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

	// Forecast
	get_forecast_data(&http, rtc);
}

void loop() {

}