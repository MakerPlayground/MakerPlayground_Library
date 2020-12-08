#ifndef MP_RGB_LED_CA_H
#define MP_RGB_LED_CA_H

#include "MP_DEVICE.h"

class MP_RGB_LED_CA
{
public:
	MP_RGB_LED_CA(uint8_t r, uint8_t g, uint8_t b);

	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	void on(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);
	void off();

private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
	uint8_t brightness = 0;
};

#endif
