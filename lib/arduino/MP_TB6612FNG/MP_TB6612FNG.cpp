#include "MP_TB6612FNG.h"

MP_TB6612FNG::MP_TB6612FNG()
{
}

int MP_TB6612FNG::init()
{
  Wire.begin();
  motor.init();
  return MP_ERR_OK;
}

void MP_TB6612FNG::update(unsigned long current_time)
{
}

void MP_TB6612FNG::printStatus()
{
}

motor_channel_type_t MP_TB6612FNG::toDeviceChannel(uint8_t ch)
{
  return ch == 1 ? MOTOR_CHA : MOTOR_CHB;
}

void MP_TB6612FNG::motorOn(uint8_t channel, int direction, int percent)
{
  motor.dcMotorRun(toDeviceChannel(channel), (int) ((direction ? 1 : -1) * 255 * percent));
}

void MP_TB6612FNG::motorBrake(uint8_t channel)
{
  motor.dcMotorBrake(toDeviceChannel(channel));
}

void MP_TB6612FNG::motorOff(uint8_t channel)
{
  motor.dcMotorStop(toDeviceChannel(channel));
}