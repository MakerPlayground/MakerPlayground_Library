#ifndef MP_DS18B20_H
#define MP_DS18B20_H

#include "Arduino.h"
#include "MP_DEVICE.h"
#include <DallasTemperature.h>

class MP_DS18B20 {
public:
    MP_DS18B20(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

    double getTemperature();
private:
    OneWire wire;
    DallasTemperature sensors;
    int numberOfDevices; // Number of temperature devices found
    DeviceAddress tempDeviceAddress;
    double temperature = 0;
    unsigned long lastMillis = 0;
};

#endif