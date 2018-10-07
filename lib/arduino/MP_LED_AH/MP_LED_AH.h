#ifndef MP_LED_AH_H
#define MP_LED_AH_H

#include <Arduino.h>
#ifdef ESP32
#include "ESP32_Polyfill.h"
#endif

class MP_LED_AH
{
public:
	MP_LED_AH(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void on(int brightness);
	void off();
	
private:
	uint8_t pin;
	const String tag;
	int brightness;
};

#endif
