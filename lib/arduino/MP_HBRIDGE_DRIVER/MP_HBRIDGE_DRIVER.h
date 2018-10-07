#ifndef MP_HBRIDGE_DRIVER_H
#define MP_HBRIDGE_DRIVER_H

#include <Arduino.h>
#ifdef ESP32
#include "ESP32_Polyfill.h"
#endif

class MP_HBRIDGE_DRIVER
{
public:
	MP_HBRIDGE_DRIVER(uint8_t inA, uint8_t inB);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void on(char dir[], int speed);
	void off();

private:
	uint8_t inA;
	uint8_t inB;
};

#endif
