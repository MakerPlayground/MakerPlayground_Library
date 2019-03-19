#include "MP_VL53L0X.h"
#include <Wire.h>
#include <VL53L0X.h>

//#define LONG_RANGE
//#define HIGH_SPEED
//#define HIGH_ACCURACY

MP_VL53L0X::MP_VL53L0X()
{
}

int MP_VL53L0X::init()  
{
    Wire.begin();
    if(!sensor.init()) {
        return ERR_CONNECT_DEVICE;
    }
    sensor.setTimeout(500);
#if defined LONG_RANGE
    // lower the return signal rate limit (default is 0.25 MCPS)
    sensor.setSignalRateLimit(0.1);
    // increase laser pulse periods (defaults are 14 and 10 PCLKs)
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
    // reduce timing budget to 20 ms (default is about 33 ms)
    sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
    // increase timing budget to 200 ms
    sensor.setMeasurementTimingBudget(200000);
#endif
    return ERR_OK;
}

void MP_VL53L0X::update(unsigned long current_time)
{
    if (current_time >= nextReading)
    {
        nextReading = current_time + 50;        // next reading should happen at least 50ms later otherwise the sound
        cm = 0.1 * sensor.readRangeSingleMillimeters();
        isTimeOut = sensor.timeoutOccurred();
    }
}

void MP_VL53L0X::printStatus()
{
    if (!isTimeOut) {
        Serial.print(F("distance (cm.) = "));
        Serial.println(this->cm);
    } else {
        Serial.print(F("Cannot connect to sensor"));
    }
}

double MP_VL53L0X::getDistance() 
{
    return cm;
}
