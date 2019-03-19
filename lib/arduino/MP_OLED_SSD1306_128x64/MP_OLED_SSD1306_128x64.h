#ifndef MP_OLED_SSD1306_128x64_H
#define MP_OLED_SSD1306_128x64_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class MP_OLED_SSD1306_128x64
{
public:
	MP_OLED_SSD1306_128x64();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void showText(int line, char* text);
	void showNumber(int line, char* label, double value);
	void clearScreen();

private:
    Adafruit_SSD1306 display;
};

#endif
