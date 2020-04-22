#ifndef MP_TFT_M5Stack_H
#define MP_TFT_M5Stack_H

#include "MP_DEVICE.h"
// fool platformio to include SD.h and Wire.h as they are needed by M5Stack.h as platformio compile the whole
// library even though we need only M5Display.h and it's library dependency generator is not smart enough to
// list dependency recursively
#include <SD.h>
#include <Wire.h>
#include <M5Display.h>
#include <M5Stack.h>

#define MAX_ENTRY_COUNT 20

class MP_TFT_M5Stack
{
public:
	MP_TFT_M5Stack();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color);
	void clearRow(uint8_t row);
	void clearScreen();

private:
    M5Display display;
	void initRowHeights();
	uint8_t row_heights[MAX_ENTRY_COUNT];
	
	uint16_t getColorFromColorName(uint8_t color);
};

#endif
