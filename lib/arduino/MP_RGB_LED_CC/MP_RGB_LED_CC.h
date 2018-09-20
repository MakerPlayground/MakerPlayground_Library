#ifndef MP_RGB_LED_CC_H
#define MP_RGB_LED_CC_H

#include <Arduino.h>

class MP_RGB_LED_CC
{
public:
	MP_RGB_LED_CC(uint8_t r, uint8_t g, uint8_t b, const String &tag);

	void init();
	void on(int red, int green, int blue, int brightness);
	void off();

private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	const String tag;
};

#endif
