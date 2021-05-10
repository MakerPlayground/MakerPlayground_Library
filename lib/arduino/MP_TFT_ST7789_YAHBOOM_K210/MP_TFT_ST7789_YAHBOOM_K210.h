#ifndef MP_TFT_ST7789_YAHBOOM_K210_H
#define MP_TFT_ST7789_YAHBOOM_K210_H

#include "MP_DEVICE.h"
#include <Sipeed_ST7789.h>

#define MAX_ENTRY_COUNT 16

class MP_TFT_ST7789_YAHBOOM_K210
{
public:
	MP_TFT_ST7789_YAHBOOM_K210();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color);
	void showImage(MP_IMAGE image);
	void clearRow(uint8_t row);
	void clearScreen();

private:
    SPIClass spi;
    Sipeed_ST7789 lcd;
	uint8_t row_heights[MAX_ENTRY_COUNT];

	void initRowHeights();
	uint16_t getColorFromColorName(uint8_t color);
	uint16_t getRowStartY(uint8_t index);
};

#endif
