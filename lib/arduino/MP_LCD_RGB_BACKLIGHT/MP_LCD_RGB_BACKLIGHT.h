#ifndef MP_LCD_RGB_BACKLIGHT_H
#define MP_LCD_RGB_BACKLIGHT_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "rgb_lcd.h"

#define MAX_ENTRY_COUNT 8

class MP_LCD_RGB_BACKLIGHT
{
public:
	MP_LCD_RGB_BACKLIGHT();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color);
	void clearRow(uint8_t row);
	void clearScreen();

private:
    rgb_lcd lcd;
};

#endif
