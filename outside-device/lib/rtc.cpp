#include <Arduino.h>
#include "RTClib.h"
#include <Wire.h>
#include <SPI.h>

RTC_DS3231 rtc;

// char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  // delay(5000);
  Serial.begin(115200);
  // Wire.begin(21, 14);
  Serial.println("Wake up");

  // if (! rtc.begin()) {
  //   Serial.println("Couldn't find RTC");
  //   Serial.flush();
  //   while (1) delay(10);
  // }
  // 
  // if (rtc.lostPower()) {
  //   Serial.println("RTC lost power, let's set the time!");
  //   // When time needs to be set on a new device, or after a power loss, the
  //   // following line sets the RTC to the date & time this sketch was compiled
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // }


  // esp_sleep_enable_timer_wakeup(5000000);
  // Serial.println("Going to sleep!");
  // esp_deep_sleep_start();
 // Set the alarm to trigger every 10 minutes
}

void loop () {

    delay(3000);
}

