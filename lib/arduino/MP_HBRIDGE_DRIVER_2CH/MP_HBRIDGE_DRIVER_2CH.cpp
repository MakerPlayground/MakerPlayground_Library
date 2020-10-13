#include "MP_HBRIDGE_DRIVER_2CH.h"

MP_HBRIDGE_DRIVER_2CH::MP_HBRIDGE_DRIVER_2CH(uint8_t M1A, uint8_t M1B, uint8_t M2A, uint8_t M2B)
	: M1A(M1A)
	, M1B(M1B)
	, M2A(M2A)
	, M2B(M2B)
{
}

int MP_HBRIDGE_DRIVER_2CH::init()
{
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  motorOff(1);
  motorOff(2);
	return MP_ERR_OK;
}

void MP_HBRIDGE_DRIVER_2CH::update(unsigned long current_time) 
{
}

void MP_HBRIDGE_DRIVER_2CH::printStatus() 
{
}

void MP_HBRIDGE_DRIVER_2CH::motorOn(uint8_t channel, int dir, int speed)
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
	else if (channel == 2) {
    if (dir == 1) {
      analogWrite(M2A, speed);
      analogWrite(M2B, 0);
    } else {
      analogWrite(M2A, 0);
      analogWrite(M2B, speed);
    }
  }
}

void MP_HBRIDGE_DRIVER_2CH::motorOff(uint8_t channel)
{
  if (channel == 1) {
    analogWrite(M1A, 255);
    analogWrite(M1B, 255);
  } else if (channel == 2) {
    analogWrite(M2A, 255);
    analogWrite(M2B, 255);
  }
}

void MP_HBRIDGE_DRIVER_2CH::motorBrake(uint8_t channel)
{
  if (channel == 1) {
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
  } else if (channel == 2) {
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
  }
}