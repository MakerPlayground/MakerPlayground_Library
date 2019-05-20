#ifndef MP_VL53L0X_H
#define MP_VL53L0X_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <VL53L0X.h>

class MP_VL53L0X
{
public:
    MP_VL53L0X(String mode);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    double getDistance();

private:
    double cm = 0.0;
    VL53L0X sensor;
    bool isTimeOut = false;
    unsigned long nextReading;
    String mode;
};

#endif