#ifndef MP_WS281X_STRIP_GRB_H
#define MP_WS281X_STRIP_GRB_H

#include "MP_DEVICE.h"
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

class MP_WS281X_STRIP_GRB
{
public:
	MP_WS281X_STRIP_GRB(uint8_t pin, int numPixel);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void setColor(int index, int red, int green, int blue);
	void fillColor(int startIndex, int endIndex, int red, int green, int blue);
	void setBrightness(int brightness);
	void clear();

private:
	uint8_t pin;
	Adafruit_NeoPixel pixels;
};

#endif
