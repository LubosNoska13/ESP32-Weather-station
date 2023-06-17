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
extern Adafruit_SH1106G display;

// Setup Display
void setup_display();

// Display values
void displayData(const char* title, const uint8_t* main_icon, int main_icon_size, float value, int32_t rssi);

#endif