#ifndef MP_TFT_M5StickC_H
#define MP_TFT_M5StickC_H

#include "MP_DEVICE.h"
#include <M5StickC.h>

#define MAX_ENTRY_COUNT 6

class MP_TFT_M5StickC
{
public:
	MP_TFT_M5StickC();
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
