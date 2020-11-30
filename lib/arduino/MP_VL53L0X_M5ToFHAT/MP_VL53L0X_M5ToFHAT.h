#ifndef MP_VL53L0X_M5ToFHAT_H
#define MP_VL53L0X_M5ToFHAT_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <VL53L0X.h>

class MP_VL53L0X_M5ToFHAT
{
public:
    // integrated device isn't currently support property so we hard-coded them for now
    MP_VL53L0X_M5ToFHAT(uint8_t mode=1, uint8_t useLongRange=true);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    double getDistance();

private:
    double cm = 0.0;
    TwoWire bus;    // use custom wire instance
    VL53L0X sensor;
    bool isTimeOut = false;
    unsigned long nextReading = 0;
    uint8_t mode;
    uint8_t useLongRange;
};

#endif