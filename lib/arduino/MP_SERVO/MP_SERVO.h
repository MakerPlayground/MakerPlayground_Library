#ifndef MP_SERVO_H
#define MP_SERVO_H

#include "MP_DEVICE.h"
#include <Servo.h>
class MP_SERVO
{
public:
	MP_SERVO(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void moveto(int degree);

private:
	uint8_t pin;
	Servo myservo;
	int degree;
};

#endif
