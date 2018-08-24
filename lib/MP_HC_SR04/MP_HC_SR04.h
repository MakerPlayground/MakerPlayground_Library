#ifndef MP_HC_SR04_H
#define MP_HC_SR04_H

#include <Arduino.h>

class MP_HC_SR04
{
public:
	MP_HC_SR04(uint8_t echo, uint8_t trig, const String &tag);

	void init();
	double getDistance();

private:
	uint8_t trig;
	uint8_t echo;
	const String tag;
}
#endif
