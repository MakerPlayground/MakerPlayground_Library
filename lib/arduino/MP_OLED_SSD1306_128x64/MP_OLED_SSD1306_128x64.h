#ifndef MP_OLED_SSD1306_128x64_H
#define MP_OLED_SSD1306_128x64_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MAX_ENTRY_COUNT 8

class MP_OLED_SSD1306_128x64
{
public:
	MP_OLED_SSD1306_128x64();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void showTextAtRow(uint8_t row, char* text, char* size, char* align, char* color);
	void showNumberAtRow(uint8_t row, char* label, double value, double decimalPlaces, char* size, char* align, char* color);
	void clearRow(uint8_t row);
	void clearScreen();

private:
	void initRowHeights();

	Adafruit_SSD1306 display;
	uint8_t row_heights[MAX_ENTRY_COUNT];
};

#endif
