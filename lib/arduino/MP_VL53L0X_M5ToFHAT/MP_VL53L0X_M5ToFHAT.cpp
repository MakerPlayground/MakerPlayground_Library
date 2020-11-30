#include "MP_VL53L0X_M5ToFHAT.h"
#include <Wire.h>
#include <VL53L0X.h>

MP_VL53L0X_M5ToFHAT::MP_VL53L0X_M5ToFHAT(uint8_t mode, uint8_t useLongRange)
    : bus(2)    // Wire and Wire1 use bus_num = 0 and 1 respectively so we use bus_num = 2
    , mode(mode)
    , useLongRange(useLongRange)
{
}

int MP_VL53L0X_M5ToFHAT::init()  
{
    bus.begin(0, 26, 400000);   // use custom wire instance
    sensor.setBus(&bus);
    if(!sensor.init()) {
        return MP_ERR_CONNECT_DEVICE;
    }
    sensor.setTimeout(500);
    if (useLongRange) {
        // lower the return signal rate limit (default is 0.25 MCPS)
        sensor.setSignalRateLimit(0.1);
        // increase laser pulse periods (defaults are 14 and 10 PCLKs)
        sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
        sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
    }

    if (mode == 1) { // HIGH_SPEED
        sensor.setMeasurementTimingBudget(20000);   // reduce timing budget to 20 ms (default is about 33 ms)
    }
    else if (mode == 0) { // HIGH_ACCURACY
        sensor.setMeasurementTimingBudget(200000);  // increase timing budget to 200 ms
    }
    return MP_ERR_OK;
}

void MP_VL53L0X_M5ToFHAT::update(unsigned long current_time)
{
    if (current_time >= nextReading)
    {
        nextReading = current_time + 50;        // next reading should happen at least 50ms later otherwise the sound
        cm = 0.1 * sensor.readRangeSingleMillimeters();
        isTimeOut = sensor.timeoutOccurred();
    }
}

void MP_VL53L0X_M5ToFHAT::printStatus()
{
    if (!isTimeOut) {
        Serial.print(F("distance (cm.) = "));
        Serial.println(this->cm);
    } else {
        Serial.print(F("Cannot connect to sensor"));
    }
}

double MP_VL53L0X_M5ToFHAT::getDistance() 
{
    return cm;
}
