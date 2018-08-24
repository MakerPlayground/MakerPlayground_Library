#ifndef MP_MQ3_H
#define MP_MQ3_H

#include <Arduino.h>

class MP_MQ3
{
public:
	MP_MQ3(uint8_t pin, const Sting &tag);

	void init();
	double getPercent();

private:
	uint8_t pin;
	const String tag;
};

#endif
