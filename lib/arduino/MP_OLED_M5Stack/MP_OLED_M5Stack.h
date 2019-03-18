#ifndef MP_OLED_M5Stack_H
#define MP_OLED_M5Stack_H

#include "MP_DEVICE.h"
// fool platformio to include SD.h and Wire.h as they are needed by M5Stack.h as platformio compile the whole
// library even though we need only M5Display.h and it's library dependency generator is not smart enough to
// list dependency recursively
#include <SD.h>
#include <Wire.h>
#include <M5Display.h>

class MP_OLED_M5Stack
{
public:
	MP_OLED_M5Stack();
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void showText(int line, char* text);
	void showNumber(int line, char* label, double value);
	void clearScreen();

private:
    M5Display display;
};

#endif
