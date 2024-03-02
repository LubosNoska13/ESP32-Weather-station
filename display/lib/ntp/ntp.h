#ifndef RTC_H 
#define RTC_H

#include <time.h>
#include "config.h"
#include "RTClib.h"

class NTP {
    private:
        const char* SERVER = ntpServer;
        const long GMT_OFFSET = gmtOffset_sec;
        const int DAYLIGHT_OFFSET = daylightOffset_sec;
    
    public:
        void setup();
        void set_date(RTC_DS3231* rtc);
};

#endif // RTC_H