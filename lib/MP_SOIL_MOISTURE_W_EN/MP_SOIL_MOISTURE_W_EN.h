#ifndef MP_SOIL_MOISTURE_W_EN_H
#define MP_SOIL_MOISTURE_W_EN_H

#include <Arduino.h>
class MP_SOIL_MOISTURE_W_EN
{
public:
	MP_SOIL_MOISTURE_W_EN(uint8_t data, uint8_t en,const String &tag);

	void init();
	double getPercent();

private:
	uint8_t data;
	uint8_t en;
	const String tag;

};

#endif
