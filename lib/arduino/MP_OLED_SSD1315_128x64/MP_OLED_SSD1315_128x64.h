#ifndef MP_OLED_SSD1315_128x64_H
#define MP_OLED_SSD1315_128x64_H

#include "MP_DEVICE.h"
#include <U8g2lib.h>
#include <Wire.h>

#define MAX_ENTRY_COUNT 8

class MP_OLED_SSD1315_128x64
{
public:
	MP_OLED_SSD1315_128x64();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color);
	void clearRow(uint8_t row);
	void clearScreen();

private:
	void initRowHeights();
	void initCacheValues();
	void drawAll();
	
	U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2;
	String texts[MAX_ENTRY_COUNT];
	uint8_t aligns[MAX_ENTRY_COUNT];
	uint8_t sizes[MAX_ENTRY_COUNT];
};

#endif
