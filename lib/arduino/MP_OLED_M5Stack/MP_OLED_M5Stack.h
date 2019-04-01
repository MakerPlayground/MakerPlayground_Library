#ifndef MP_OLED_M5Stack_H
#define MP_OLED_M5Stack_H

#define MAX_ENTRY_COUNT 10

#include "MP_DEVICE.h"
// fool platformio to include SD.h and Wire.h as they are needed by M5Stack.h as platformio compile the whole
// library even though we need only M5Display.h and it's library dependency generator is not smart enough to
// list dependency recursively
#include <SD.h>
#include <Wire.h>
#include <M5Display.h>
#include <M5Stack.h>

class MP_OLED_M5Stack
{
public:
	MP_OLED_M5Stack();
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
    M5Display display;
	bool isDirty = false;
	unsigned long last_update = 0;
	uint8_t getSizeFromSizeName(char* size);
	uint16_t getColorFromColorName(char* color);

	struct messageEntry {
		uint8_t size = 1;
		uint16_t color = 1;
		char message[32] = "";
	};

	struct messageEntryWithPosition {
		uint8_t x = -1;
		uint8_t y = -1;
		uint8_t size = 1;
		uint16_t color = 1;
		char message[32] = "";
	};

	uint8_t entryWithPositionCount = 0;
	struct messageEntry entries[MAX_ENTRY_COUNT];
	struct messageEntryWithPosition entriesWithPosition[MAX_ENTRY_COUNT];
};

#endif
