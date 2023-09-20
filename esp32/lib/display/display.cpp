#include <string.h>
#include "display.h"
#include "icons.h"

// Setup Display
void Display::setup() {
    display.begin(I2C_ADDRESS, true);
    display.display();
    delay(2000);
    display.clearDisplay();
}

// Private Helper Methods
void Display::show_title(const char* title) {
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 1);
    display.println(title);
} 

void Display::show_wifi(int32_t rssi) {
    // Wifi signal icon
    if (rssi == 0) {
        display.drawBitmap(display.width()-14, 0, wifi_icon_no_signal, 14, 14, 1);
    }
    else if (rssi >= -60) {
        display.drawBitmap(display.width()-13, 0, wifi_icon_great, 13, 13, 1);
    }
    else if (rssi >= -75) {
        display.drawBitmap(display.width()-13, 0, wifi_icon_good, 13, 13, 1);
    }
    else if (rssi >= -90) {
        display.drawBitmap(display.width()-13, 0, wifi_icon_bad, 13, 13, 1);
    }
    else {
        display.drawBitmap(display.width()-14, 0, wifi_icon_no_signal, 14, 14, 1);
    }
}

void Display::show_mqtt() {
    display.drawBitmap(display.width()-13-19, -1, connection_icon, 17, 17, 1);
}

void Display::show_main_value(const float value, const int8_t* idx) {
    display.setTextSize(2);
    display.setCursor(65, 35);

    if (*idx == 0 || *idx == 1)
        display.println((int)value);
    else 
        display.println(value);
}
// Display values
void Display::showData(JsonDocument& doc, const int8_t* idx) {
    display.clearDisplay();
    
    char title[18];

    switch (*idx) {
        //display.drawBitmap(X_POSITION, Y_POSITION, ICON, ICON_X_SIZE, ICON_Y_SIZE, COLOR);
        case 0:
            strcpy(title, "Temperature");
            display.drawBitmap(2, 15, temperature_icon, 50, 50, 1);
            display.drawBitmap(90, 32, celsius_icon, 14, 14, 1);
            break;
        case 1:
            strcpy(title, "Humidity");
            display.drawBitmap(2, 15, humidity_icon, 52, 52, 1);
            display.drawBitmap(90, 32, percent_icon, 13, 13, 1);
            break;
        case 2:
            strcpy(title, "Carbon Monoxide");
            display.drawBitmap(-10, 5, co_icon, 70, 70, 1);
            break;
        case 3:
            strcpy(title, "Carbon Dioxide");
            display.drawBitmap(-5, 5, co2_icon, 70, 70, 1);
            break;
        default:
            break;
    }

    show_title(title);
    show_wifi(doc["Wifi"]);
    show_mqtt();
    show_main_value(doc[title], idx);

    display.display();
}
