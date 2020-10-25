#ifndef MP_TCS3200_H
#define MP_TCS3200_H

#include "MP_DEVICE.h"
#include <Wire.h>

class MP_TCS3200
{
public:
	MP_TCS3200(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out, uint8_t LED);
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
	uint8_t s0;
	uint8_t s1;
	uint8_t s2;
	uint8_t s3;
	uint8_t out;
	uint8_t LED;

	int red = 0;
	int green = 0;
	int blue = 0;
	double hsv[3];

	unsigned long next_reading = 0;

	int8_t color_code = -1;
	String current_color;
	int rgb2hsv(int r,int g,int b,double out[]);
};

#endif
