#ifndef MP_RELAY_H
#define MP_RELAY_H

#include <Arduino.h>

class MP_RELAY
{
public:
	MP_RELAY(uint8_t pin, const String &tag);

	void init();
	void on();
	void off();

private:
	uint8_t pin;
	const String tag;
};

#endif
