#include "MP_SERVO.h"

MP_SERVO::MP_SERVO(uint8_t pin,const String &tag)
  : pin(pin),tag(tag)
{
}

void MP_SERVO::init()
{
	myservo.attach(pin);
}

void MP_SERVO::moveto(int degree)
{
	myservo.write(degree);
}
