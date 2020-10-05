#ifndef MP_MAX31850K_H
#define MP_MAX31850K_H

#include "Arduino.h"
#include "MP_DEVICE.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class MP_MAX31850K {
public:
  MP_MAX31850K(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();  
  double getTemperature();

private:
  OneWire wire;
  DallasTemperature sensors;
  DeviceAddress tempDeviceAddress;
  double temperature = 0;
  unsigned long lastMillis = 0;
};

#endif