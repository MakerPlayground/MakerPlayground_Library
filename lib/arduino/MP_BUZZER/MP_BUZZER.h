#ifndef MP_BUZZER_H
#define MP_BUZZER_H

#include <Arduino.h>
#ifdef ESP32
#include "ESP32_Polyfill.h"
#endif

class MP_BUZZER
{
public:
	MP_BUZZER(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void beep();
	void play(double frequency, double duration);

private:
	uint8_t pin;
	boolean playing;
	unsigned long endTime;
};

#endif
