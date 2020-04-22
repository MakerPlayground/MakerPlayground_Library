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

	void showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color);
	void clearRow(uint8_t row);
	void clearScreen();

private:
	void initRowHeights();

	Adafruit_SSD1306 display;
	uint8_t row_heights[MAX_ENTRY_COUNT];
};

#endif
