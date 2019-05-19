#ifndef MP_OLED_SSD1306_128x64_H
#define MP_OLED_SSD1306_128x64_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MAX_ENTRY_COUNT 5

class MP_OLED_SSD1306_128x64
{
public:
	MP_OLED_SSD1306_128x64();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void showTextAtLine(int line, char* text, char* size, char* color);
	void showTextAtPosition(int x, int y, char* text, char* size, char* color);
	void showNumberAtLine(int line, char* label, double value, double decimalPlaces, char* size, char* color);
	void showNumberAtPosition(int x, int y, char* label, double value, double decimalPlaces, char* size, char* color);
	void clearLine(int line);
	void clearScreen();

private:
    Adafruit_SSD1306 display;
	void show();

	struct messageEntry {
		uint8_t size = 1;
		char message[32] = "";
	};

	struct messageEntryWithPosition {
		uint8_t x = -1;
		uint8_t y = -1;
		uint8_t size = 1;
		char message[32] = "";
	};

	uint8_t entryWithPositionCount = 0;
	struct messageEntry entries[MAX_ENTRY_COUNT];
	struct messageEntryWithPosition entriesWithPosition[MAX_ENTRY_COUNT];
};

#endif
