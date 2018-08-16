#ifndef MP_SERVO_H
#define MP_SERVO_H

#include <Arduino.h>
#include <Servo.h>
class MP_SERVO
{
public:
	MP_SERVO(uint8_t pin,const String &tag);

	void moveto(int degree);
	void init();

private:
	uint8_t pin;
	Servo myservo;
	const String tag;
};

#endif
