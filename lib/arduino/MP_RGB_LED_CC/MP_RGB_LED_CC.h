#ifndef MP_RGB_LED_CC_H
#define MP_RGB_LED_CC_H

#include "MP_DEVICE.h"

class MP_RGB_LED_CC
{
public:
	MP_RGB_LED_CC(uint8_t r, uint8_t g, uint8_t b);

	int init();
	void update(unsigned long current_time);
	void printStatus();

	void on(int red, int green, int blue, int brightness);
	void off();

private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	int red;
	int green;
	int blue;
	int brightness;
};

#endif
