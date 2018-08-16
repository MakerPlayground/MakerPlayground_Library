#ifndef MP_TRIMPOT_H
#define MP_TRIMPOT_H

#include <Arduino.h>
class MP_TRIMPOT
{
public:
	MP_TRIMPOT(uint8_t pin, const String &tag);

	void init();
	double getPercent();

private:
	uint8_t pin;
	const String tag;
};

#endif
