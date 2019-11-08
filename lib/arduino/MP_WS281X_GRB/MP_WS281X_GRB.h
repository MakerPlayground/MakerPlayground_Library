#ifndef MP_WS281X_GRB_H
#define MP_WS281X_GRB_H

#include "MP_DEVICE.h"
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

class MP_WS281X_GRB
{
public:
	MP_WS281X_GRB(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

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
