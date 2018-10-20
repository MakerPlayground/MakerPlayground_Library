#ifndef MP_IR_REFLECTOR_H
#define MP_IR_REFLECTOR_H

#include "MP_DEVICE.h"

class MP_IR_REFLECTOR
{
public:
	MP_IR_REFLECTOR(uint8_t pin, const String &tag);

	void init();
	int isDetected();
	int isNotDetected();

private:
	uint8_t pin;
	const String tag;
};
#endif
