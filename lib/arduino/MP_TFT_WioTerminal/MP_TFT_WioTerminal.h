#ifndef MP_TFT_WioTerminal_H
#define MP_TFT_WioTerminal_H

#include "MP_DEVICE.h"
#include "TFT_eSPI.h"

#define MAX_ENTRY_COUNT 20

class MP_TFT_WioTerminal
{
public:
	MP_TFT_WioTerminal();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color);
	void clearRow(uint8_t row);
	void clearScreen();

private:
    TFT_eSPI display;
	void initRowHeights();
	uint8_t row_heights[MAX_ENTRY_COUNT];
	
	uint16_t getColorFromColorName(uint8_t color);
};

#endif
