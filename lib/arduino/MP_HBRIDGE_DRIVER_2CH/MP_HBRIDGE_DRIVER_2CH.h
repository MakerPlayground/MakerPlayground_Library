#ifndef MP_HBRIDGE_DRIVER_2CH_H
#define MP_HBRIDGE_DRIVER_2CH_H

#include "MP_DEVICE.h"

class MP_HBRIDGE_DRIVER_2CH
{
public:
	MP_HBRIDGE_DRIVER_2CH(uint8_t M1A, uint8_t M1B, uint8_t M2A, uint8_t M2B);
	int init();
	void update(unsigned long current_time);
	void printStatus();

  /* DC Motor */
  void motorOn(uint8_t channel, int dir, int speed);
  void motorOff(uint8_t channel);
  void motorBrake(uint8_t channel);

private:
	uint8_t M1A, M1B, M2A, M2B;
};

#endif
