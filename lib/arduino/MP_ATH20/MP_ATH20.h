#ifndef MP_ATH20_H
#define MP_ATH20_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "ATH20.h"

class MP_ATH20
{
public:
	MP_ATH20();

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getTemperature();
	double getHumidity();

private:
	ATH20 ATH;
	uint8_t pin;
	
	double humidity;
	double celcius;
  bool isValid;
};

#endif
