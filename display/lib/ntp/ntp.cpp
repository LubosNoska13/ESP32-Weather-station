#include "ntp.h"

void NTP::setup() {
	// Init and get the time
	configTime(GMT_OFFSET, DAYLIGHT_OFFSET, SERVER);
}

void NTP::set_date(RTC_DS3231* rtc) {
	struct tm timeinfo;
	if(!getLocalTime(&timeinfo)){
		debug("Failed to obtain time");
		return;
	}

    // Print the obtained time
	Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    // Set the time on the RTC
    rtc->adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, 
                        timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));
}


