#include "MP_HBRIDGE_DRIVER_1CH.h"

MP_HBRIDGE_DRIVER_1CH::MP_HBRIDGE_DRIVER_1CH(uint8_t M1A, uint8_t M1B)
	: M1A(M1A)
	, M1B(M1B)
{
}

int MP_HBRIDGE_DRIVER_1CH::init()
{
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  motorOff(1);
	return MP_ERR_OK;
}

void MP_HBRIDGE_DRIVER_1CH::update(unsigned long current_time) 
{
}

void MP_HBRIDGE_DRIVER_1CH::printStatus() 
{
}

void MP_HBRIDGE_DRIVER_1CH::motorOn(uint8_t channel, int dir, int speed)
{
	speed = map(speed, 0, 100, 0, 255);
  // dir: Forward - 1, Backward - 0
  if (channel == 1) {
    if (dir == 1) {
      analogWrite(M1A, speed);
      analogWrite(M1B, 0);
    } else {
      analogWrite(M1A, 0);
      analogWrite(M1B, speed);
    }
  }
}

void MP_HBRIDGE_DRIVER_1CH::motorOff(uint8_t channel)
{
  if (channel == 1) {
    analogWrite(M1A, 255);
    analogWrite(M1B, 255);
  }
}

void MP_HBRIDGE_DRIVER_1CH::motorBrake(uint8_t channel)
{
  if (channel == 1) {
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
  }
}