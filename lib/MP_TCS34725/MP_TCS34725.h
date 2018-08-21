#ifndef MP_TCS34725_H
#define MP_TCS34725_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

class MP_TCS34725
{
public:
	MP_TCS34725(const String &tag);
	void init();
	int isColor(char color[]);

private:
	const String tag;
};

#endif
