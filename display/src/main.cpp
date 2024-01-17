#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// LCD Display pins
#define TFT_RST       4
#define TFT_DC        5
#define TFT_CS        34
#define TFT_MOSI      35
#define TFT_CLK       36
#define TFT_MISO      37


void setup() {
	// Initialize display
	display.begin();
	display.fillScreen(ILI9341_BLACK);

}

void loop() {

}