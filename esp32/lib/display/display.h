#ifndef DISPLAY_H
#define DISPLAY_H

// Oled display library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Oled display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define i2c_Address 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// Oled display
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Setup Display
void setup_display(){
    display.begin(i2c_Address, true);
    display.display();
    delay(2000);
    display.clearDisplay();
}

// Display values
void displayData(const char* title, const uint8_t* main_icon, int main_icon_size, float value, int32_t rssi){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 1);

    // Title
    display.println(title);

    // Wifi signal icon
    if (rssi == 0){
        display.drawBitmap(display.width()-14, 0, wifi_icon_no_signal, 14, 14, 1);
    }
    else if (rssi >= -60){
        display.drawBitmap(display.width()-13, 0, wifi_icon_great, 13, 13, 1);
    }
    else if (rssi >= -75){
        display.drawBitmap(display.width()-13, 0, wifi_icon_good, 13, 13, 1);
    }
    else if (rssi >= -90){
        display.drawBitmap(display.width()-13, 0, wifi_icon_bad, 13, 13, 1);
    }
    else {
        display.drawBitmap(display.width()-14, 0, wifi_icon_no_signal, 14, 14, 1);
    }
    
    // Mqtt connection icon
    display.drawBitmap(display.width()-13-19, -1, connection_icon, 17, 17, 1);

    if (title == "Temperature" || title == "Humidity") {
        display.drawBitmap(2, 15, main_icon, main_icon_size, main_icon_size, 1);
        if (title == "Temperature") {
        display.drawBitmap(90, 32, celsius_icon, 14, 14, 1);
        } else {
        display.drawBitmap(90, 32, percent_icon, 13, 13, 1);
        }
    }
    else if (title == "Carbon Monoxide") {
        display.drawBitmap(-10, 5, main_icon, main_icon_size, main_icon_size, 1);
    }
    else if (title == "Carbon Dioxide") {
        display.drawBitmap(-5, 5, main_icon, main_icon_size, main_icon_size, 1);
    }
    display.setTextSize(2);
    display.setCursor(65, 35);
    if (title == "Temperature") {
            display.println((int)value);
        } else if (title == "Humidity") {
            display.println((int)value);
        } else {
            display.println(value);
        }
    
    display.display();
}

#endif