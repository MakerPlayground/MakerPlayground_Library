#ifndef MP_VEML6070_270kOhm_H
#define MP_VEML6070_270kOhm_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <Adafruit_VEML6070.h>

class MP_VEML6070_270kOhm
{
public:
	MP_VEML6070_270kOhm(uint8_t readingMode);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	bool checkRiskLevel(uint8_t risk);
  uint8_t getUV_Index();

private:
	Adafruit_VEML6070 uv;
	uint8_t readingMode;
	double value;
	uint8_t uvIndex;
	unsigned long nextReading;
	void convergeValue();
};

#endif