#ifndef MP_LIGHT_SENSOR_H
#define MP_LIGHT_SENSOR_H

#include <Arduino.h>
class MP_LIGHT_SENSOR
{
public:
	MP_LIGHT_SENSOR(uint8_t pin, const String &tag);

	double getPercent();
	void init();

private:
	uint8_t pin;
	const String tag;
};

#endif
