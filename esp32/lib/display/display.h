#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <ArduinoJson.h>

/*
    Class for showing data on display:
    Device: Oled 1.3inch, 128x64 (SH1106).
    Always show title with icon and value.
*/

class Display {
    private:
        // Default values for oled display
        const uint8_t SCREEN_WIDTH = 128;
        const uint8_t SCREEN_HEIGHT = 64;
        const int8_t OLED_RESET = -1;
        const uint8_t I2C_ADDRESS = 0x3c;
        Adafruit_SH1106G display;

        // Private Helper Methods
        void show_title(const char* title);
        void show_wifi(int32_t rssi);
        void show_mqtt();
        void show_main_value(const float value, const int8_t* idx);

    public:
        Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}
        // Method that needs to be called at startup
        void setup();
        // Method to show all information on display
        void showData(JsonDocument& doc, const int8_t* idx);
};

#endif // DISPLAY_H