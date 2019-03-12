#ifndef MP_WS281X_H
#define MP_WS281X_H

#include "MP_DEVICE.h"
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

class MP_WS281X
{
public:
	MP_WS281X(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void on(int red, int green, int blue, int brightness);
	void off();

private:
	uint8_t pin;
	Adafruit_NeoPixel pixels;
	int red;
	int green;
	int blue;
	int brightness;
};

#endif