#ifndef MP_TMP007_H
#define MP_TMP007_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TMP007.h"

class MP_TMP007
{
public:
	MP_TMP007(const String &tag);

	void init();
	double getTemperature();

private:
	Adafruit_TMP007 tmp007;
	const String tag;
};

#endif
