#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>

RTC_DS3231 rtc;
RTC_DATA_ATTR int bootCount = 0;

#define CLOCK_INTERRUPT_PIN 18

void onAlarm() {
    Serial.println("Measure all data!");
}

void setup() {
    delay(5000);
    Serial.begin(9600);  
    Wire.begin(21, 14);

    // initializing the rtc
    if(!rtc.begin()) {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
        while (1) delay(10);
    }

    if(rtc.lostPower()) {
        // this will adjust to the date and time at compilation
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    //we don't need the 32K Pin, so disable it
    rtc.disable32K();

    // Making it so, that the alarm will trigger an interrupt
    pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), onAlarm, FALLING);

    // set alarm 1, 2 flag to false (so alarm 1, 2 didn't happen so far)
    // if not done, this easily leads to problems, as both register aren't reset on reboot/recompile
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);

    // stop oscillating signals at SQW Pin
    // otherwise setAlarm1 will fail
    rtc.writeSqwPinMode(DS3231_OFF);

    // turn off alarm 2 (in case it isn't off already)
    // again, this isn't done at reboot, so a previously set alarm could easily go overlooked
    rtc.disableAlarm(2);

    // schedule an alarm 10 seconds in the future
    if(!rtc.setAlarm1(
            rtc.now() + TimeSpan(0, 0, 0, 10),
            DS3231_A1_Minute // this mode triggers the alarm when the seconds match. See Doxygen for other options
    )) {
        Serial.println("Error, alarm wasn't set!");
    }else {
        Serial.println("Alarm will happen in 10 seconds!");
    }

    esp_sleep_enable_ext0_wakeup(GPIO_NUM_18, 0);

    if (rtc.alarmFired(1)) {
            rtc.clearAlarm(1);
            Serial.print(" - Alarm cleared");
        }

    esp_deep_sleep_start();
}

void loop() {

    // // the value at SQW-Pin (because of pullup 1 means no alarm)
    // Serial.print(digitalRead(CLOCK_INTERRUPT_PIN));

    // // resetting SQW and alarm 1 flag
    // // using setAlarm1, the next alarm could now be configurated
    
    // Serial.println();

    // delay(2000);
}



