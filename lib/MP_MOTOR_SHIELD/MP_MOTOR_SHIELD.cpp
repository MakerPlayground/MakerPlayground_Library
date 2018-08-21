#include "MP_MOTOR_SHIELD.h"

MP_MOTOR_SHIELD::MP_MOTOR_SHIELD(const String &tag)
	:tag(tag)
{
	myMotor = AFMS.getMotor(1);
}

void MP_MOTOR_SHIELD::init()
{
	AFMS.begin();
	direction = 1;
}

void MP_MOTOR_SHIELD::on(char dir[], uint8_t speed)
{
	if(!strcmp(dir,"CW"))
		direction = 1;
	else if(!strcmp(dir,"CW"))
		direction = 2;

	myMotor->setSpeed(speed);
	if(direction ==1)
	{
		myMotor->run(FORWARD);
	}
	else if(direction == 2)
	{
		myMotor->run(BACKWARD);
	}
}

void MP_MOTOR_SHIELD::reverse()
{
	if(direction == 1)
	{
		direction = 2;
		myMotor->run(BACKWARD);
	}
	else if(direction == 2)
	{
		direction = 1;
		myMotor->run(FORWARD);
	}
}

void MP_MOTOR_SHIELD::set_speed(uint8_t speed)
{
	myMotor->setSpeed(speed);
}

void MP_MOTOR_SHIELD::off()
{
	myMotor->setSpeed(0);
}
