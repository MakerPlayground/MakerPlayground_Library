#ifndef MP_SCT013_30A_ESP32_H
#define MP_SCT013_30A_ESP32_H

#include "MP_DEVICE.h"

class MP_SCT013_30A_ESP32
{
public:
	MP_SCT013_30A_ESP32(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getAmpere();

private:
	uint8_t pin;
	double value;
	int maxValue;
	unsigned long lastReadingTime;
	unsigned long nextResetTime;
};

#endif
