#ifndef MP_TB6612FNG_H
#define MP_TB6612FNG_H

#include "MP_DEVICE.h"
#include "Grove_Motor_Driver_TB6612FNG.h"
#include <Wire.h>

#define IKB1_I2C_ADDR 0x48
#define IKB1_INPUT_ONLY 0x00
#define IKB1_OUTPUT_ONLY 0x01
#define IKB1_BOTH 0x02
#define IKB1_MOTOR_FORWARD 1
#define IKB1_MOTOR_BACKWARD 0

class MP_TB6612FNG
{
public:

  MP_TB6612FNG();
  int init();
  void update(unsigned long current_time);
  void printStatus();

  /* DC Motor */
  void motorOn(uint8_t channel, int direction, int percent);
  void motorOff(uint8_t channel);
  void motorBrake(uint8_t channel);

  /* TODO: Stepper Motor */

private:
  MotorDriver motor;
  motor_channel_type_t toDeviceChannel(uint8_t ch);
};
#endif
