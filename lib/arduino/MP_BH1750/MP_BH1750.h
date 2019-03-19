#ifndef MP_BH1750_H
#define MP_BH1750_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "BH1750.h"

class MP_BH1750
{
public:
	MP_BH1750(bool addr_pull_up=false);

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getPercent();

private:
	BH1750 lightMeter;
	float lux = 0;
	double percent = 0.0;
	unsigned long last_update = 0;
};

#endif
