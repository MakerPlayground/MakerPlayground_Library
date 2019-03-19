#ifndef MP_APDS9960_H
#define MP_APDS9960_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "SparkFun_APDS9960.h"

class MP_APDS9960
{
public:
	MP_APDS9960();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getDistance();
	bool isGestureDetected(char c[]);
	bool isGestureNotDetected();

private:
	SparkFun_APDS9960 apds;
	bool isFailOnReading;
	uint8_t x;
	unsigned long end_time;
};

#endif
