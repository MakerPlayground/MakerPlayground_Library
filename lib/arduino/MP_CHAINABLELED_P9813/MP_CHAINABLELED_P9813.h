#ifndef MP_CHAINABLELED_P9813_H
#define MP_CHAINABLELED_P9813_H

#include "MP_DEVICE.h"
#include <ChainableLED.h>

class MP_CHAINABLELED_P9813
{
public:
	MP_CHAINABLELED_P9813(uint8_t clkPin, uint8_t dataPin, int numPixel);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void setColor(int index, int red, int green, int blue);
    void fillColor(int startIndex, int endIndex, int red, int green, int blue);
    void setBrightness(int brightness);
    void clear();

private:
	ChainableLED leds;
	int numPixel;
	int brightness;
};

#endif
