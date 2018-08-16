#ifndef MP_SOIL_MOISTURE_H
#define MP_SOIL_MOISTURE_H

#include <Arduino.h>
class MP_SOIL_MOISTURE
{
public:
	MP_SOIL_MOISTURE(uint8_t data, uint8_t en,const String &tag);

	void init();
	double getPercent();

private:
	uint8_t data;
	uint8_t en;
	const String tag;

};

#endif
