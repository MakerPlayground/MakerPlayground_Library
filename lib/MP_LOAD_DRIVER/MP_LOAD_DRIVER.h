#ifndef MP_LOAD_DRIVER_H
#define MP_LOAD_DRIVER_H

#include <Arduino.h>

class MP_LOAD_DRIVER
{
public:
	MP_LOAD_DRIVER(uint8_t pin, const String &tag);

	void init();
	void on();
	void off();

private:
	uint8_t pin;
	const String tag;
};

#endif
