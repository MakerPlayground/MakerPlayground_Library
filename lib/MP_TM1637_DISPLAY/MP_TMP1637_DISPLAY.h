#ifndef MP_TMP1637_DISPLAY_H
#define MP_TMP1637_DISPLAY_H

#include <Arduino.h>
#include "TM1637Display.h"

class MP_TMP1637_DISPLAY
{
public:
	MP_TMP1637_DISPLAY(uint8_t clk, uint8_t dio, const String &tag);

	void init();
	void showValue(double value);
	void showData(double value);
	void setBrightness(char c[]);
	void off();

private:
	int data;
	int brightness;
	TM1637Display display;
	const String tag;
};
#endif
