#ifndef MP_VL53L0X_H
#define MP_VL53L0X_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <VL53L0X.h>

class MP_VL53L0X
{
public:
    MP_VL53L0X();
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

    double getDistance();

private:
    double cm = 0.0;
    VL53L0X sensor;
    bool isTimeOut = false;
    unsigned long nextReading;
};

#endif