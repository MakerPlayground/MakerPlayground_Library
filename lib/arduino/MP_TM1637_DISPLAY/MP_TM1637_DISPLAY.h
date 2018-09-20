#ifndef MP_TM1637_DISPLAY_H
#define MP_TM1637_DISPLAY_H

#include <Arduino.h>
#include "TM1637Display.h"

class MP_TM1637_DISPLAY
{
public:
	MP_TM1637_DISPLAY(uint8_t clk, uint8_t dio);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void showValue(double value);
	void showData(double value);
	void setBrightness(char c[]);
	void off();

private:
	double data;
	uint8_t brightness;
	TM1637Display display;
};
#endif
