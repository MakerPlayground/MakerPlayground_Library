#include "MP_HC_SR04.h"

MP_HC_SR04::MP_HC_SR04(uint8_t echo, uint8_t trig, const String &tag)
	:trig(trig)
	,echo(echo)
	,tag(tag)
{
}

void MP_HC_SR04::init()
{
	pinMode(this->trig, OUTPUT);
	pinMode(this->echo, INPUT);
}

double MP_HC_SR04::getDistance()
{
	long cm = 0;
	/* loop for filter an hardware error */
	do{
		digitalWrite(trig, LOW);
		delayMicroseconds(2);
		digitalWrite(trig, HIGH);
		delayMicroseconds(5);
		digitalWrite(trig, LOW);
		cm = pulseIn(echo, HIGH) / 29.0 / 2.0;
	}while(cm > 3000);
	return cm;
}
