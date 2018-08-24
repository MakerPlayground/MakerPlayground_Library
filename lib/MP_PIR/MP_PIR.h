#ifndef MP_PIR_H
#define MP_PIR_H

#include <Arduino.h>

class MP_PIR
{
public:
	MP_PIR(uint8_t pin, const String &tag);

	void init();
	int isDetected();
	int isNotDetected();

private:
	uint8_t pin;
	const String tag;
};
#endif
