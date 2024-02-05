#ifndef MP_TCS34725_H
#define MP_TCS34725_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "SPI.h"
#include "Adafruit_TCS34725.h"

class MP_TCS34725
{
public:
	MP_TCS34725();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool isColor(uint8_t color);
	
	double getRed();
	double getGreen();
	double getBlue();
	double getHue();
	double getSaturation();
	double getValue();

private:
    Adafruit_TCS34725 tcs = Adafruit_TCS34725();
    float red, green, blue;
	double h, s, v;
	uint8_t color_code;
	unsigned long end_time;
	void rgb2hsv(double r, double g, double b, double *h, double *s, double *v );
	uint8_t hsv2ColorCode(double h, double s, double v);
};

#endif
