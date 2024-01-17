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

// Color definitions
#define black         0x0000       ///<   0,   0,   0
#define navy          0x000F       ///<   0,   0, 123
#define dark_green    0x03E0       ///<   0, 125,   0
#define dark_cyan     0x03EF    ///<   0, 125, 123
#define maroon        0x7800      ///< 123,   0,   0
#define purple        0x780F      ///< 123,   0, 123
#define light_grey    0xC618   ///< 198, 195, 198
#define dark_grey     0x7BEF    ///< 123, 125, 123
#define blue          0x001F        ///<   0,   0, 255
#define green         0x07E0       ///<   0, 255,   0
#define cyan          0x07FF        ///<   0, 255, 255
#define red           0xF800         ///< 255,   0,   0
#define magenta       0xF81F     ///< 255,   0, 255
#define yellow        0xFFE0      ///< 255, 255,   0
#define white         0xFFFF       ///< 255, 255, 255
#define orange        0xFD20      ///< 255, 165,   0
#define pink          0xFC18        ///< 255, 130, 198

#define main_color    cyan

Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

struct RectSize {
	uint16_t width;
	uint16_t height;
};

RectSize measureTextSize(String text) {
	int16_t x, y;
	uint16_t w, h;

	// Get the bounding box of the text
	display.getTextBounds(text, 0, 0, &x, &y, &w, &h);

	// Create a RectSize structure to store the width and height
	RectSize textSize;
	textSize.width = w;
	textSize.height = h;

	return textSize;
}

void displayText(String text, int color, int size, int x, int y) {
	display.setCursor(x,y);
	display.setTextColor(color);
	display.setTextSize(size);
	display.print(text);
}

void setup() {
	// Initialize display
	display.begin();
	display.fillScreen(ILI9341_BLACK);

}

void loop() {

}