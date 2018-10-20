#ifndef MP_SOIL_MOISTURE_W_EN_H
#define MP_SOIL_MOISTURE_W_EN_H

#include "MP_DEVICE.h"

class MP_SOIL_MOISTURE_W_EN
{
public:
	MP_SOIL_MOISTURE_W_EN(uint8_t data, uint8_t en);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getPercent();

private:
	uint8_t data;
	uint8_t en;
	double value;
};

#endif
