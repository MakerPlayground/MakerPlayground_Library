#ifndef MP_BUZZER_ESP32_H
#define MP_BUZZER_ESP32_H

#include <Arduino.h>

class MP_BUZZER_ESP32
{
public:
	MP_BUZZER_ESP32(uint8_t pin);
	int init();
	void update(unsigned long currentTime);
	void printStatus();
	static const char* const* ERRORS;

	void beep();
	void play(double frequency, double duration);

private:
	uint8_t pin;
	boolean playing;
	unsigned long currentTime, endTime;
};

#endif
