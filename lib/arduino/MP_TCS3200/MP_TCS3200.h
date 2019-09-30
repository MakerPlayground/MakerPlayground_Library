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

	bool isColor(char color[]);

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
	
	unsigned long next_reading = 0;

	String current_color;
};

#endif
