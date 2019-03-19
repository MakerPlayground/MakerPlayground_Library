#ifndef MP_TCS34725_H
#define MP_TCS34725_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"

class MP_TCS34725
{
public:
	MP_TCS34725();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	int isColor(char color[]); // support "Red", "Green" and "Blue"

private:
	Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
	uint16_t clear, red, green, blue;
	float h, s, v;
	unsigned long end_time;
};

#endif
