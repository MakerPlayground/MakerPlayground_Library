#ifndef MP_WATER_SENSOR
#define MP_WATER_SENSOR

#include "MP_DEVICE.h"

class MP_WATER_SENSOR
{
public:
	MP_WATER_SENSOR(uint8_t pin, const String &tag);

	void init();
	bool isWet();
	bool isDry();

private:
	uint8_t pin;
	const String tag;
};

#endif
