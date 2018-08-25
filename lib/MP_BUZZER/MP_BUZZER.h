#ifndef MP_BUZZER_H
#define MP_BUZZER_H

#include <Arduino.h>
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
};

#endif
