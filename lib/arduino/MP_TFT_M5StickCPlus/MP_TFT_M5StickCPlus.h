#ifndef MP_TFT_M5StickCPlus_H
#define MP_TFT_M5StickCPlus_H

#include "MP_DEVICE.h"
#include <M5StickCPlus.h>

#define MAX_ENTRY_COUNT 10

class MP_TFT_M5StickCPlus
{
public:
	MP_TFT_M5StickCPlus();
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
