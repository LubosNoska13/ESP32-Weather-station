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
	// Initialize
	display.begin();
	display.fillScreen(black);

	display.setFont(&small_font);
	displayText("TUE AUG 10 2021", main_color, 1, (display.width() - measureTextSize("TUE AUG 10 2021").width) / 2, 15);

	display.setFont(&big_font);
	displayText("10:30", white, 1, (display.width() - measureTextSize("10:30").width) / 2, 50);

	display.setFont(&small_font);
	displayText("PRIEVIDZA", main_color, 1, 170, 80);
	displayText("SLOVAKIA", main_color, 1, 170, 130);

	display.setFont(&big_font);
	displayText("27.5°C", white, 1, 120,115);
	display.drawBitmap(25, 65, weather_partly_cloudy, 75, 75, main_color);

	// Left-side
	display.setFont(&small_font);
	displayText("SAT", main_color, 1, (display.width() / 4) - (measureTextSize("SAT").width / 2), 165);
	displayText("1/17", white, 1, (display.width() / 4) - (measureTextSize("1/17").width / 2), 175);
	display.drawBitmap((display.width() / 4) - (45 / 2), 180, weather_lightning, 45, 45, main_color);

	displayText("SUN", main_color, 1, (display.width() / 4) - (measureTextSize("SUN").width / 2), 250);
	displayText("5:10", white, 1, (display.width() / 4) - (measureTextSize("5:10").width / 2), 262);
	displayText("20:31", white, 1, (display.width() / 4) - (measureTextSize("20:31").width / 2), 274);

	// Middle-side
	displayText("SUN", main_color, 1, (display.width() / 2) - (measureTextSize("SUN").width / 2), 165);
	displayText("1/18", white, 1, (display.width() / 2) - (measureTextSize("1/18").width / 2), 175);
	display.drawBitmap((display.width() / 2) - (45 / 2), 180, weather_pouring, 45, 45, main_color);
	display.drawBitmap((display.width() / 2) - (55 / 2), 235, moon_waning_crescent, 55, 55, main_color);

// Right-side
  displayText("MON", main_color, 1, (display.width() * 3/4) - (measureTextSize("MON").width / 2), 165);
  displayText("1/19", white, 1, (display.width() * 3/4) - (measureTextSize("1/19").width / 2), 175);
  display.drawBitmap((display.width() * 3/4) - (45 / 2), 180, weather_windy, 45, 45, main_color);
  displayText("RAINY", main_color, 1, (display.width() * 3/4) - (measureTextSize("RAINY").width / 2), 250);
  displayText("Precipitation: 50%", white, 1, (display.width() * 3/4) - (measureTextSize("Precipitation: 50%").width / 2), 262);
  displayText("Humidity:  94%", white, 1, (display.width() * 3/4) - (measureTextSize("Humidity:  94%").width / 2), 274);

}

void loop() {

}