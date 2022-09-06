#ifndef MP_PAH8001EI2G_SEEED_H
#define MP_PAH8001EI2G_SEEED_H

#include "Arduino.h"
#include "MP_DEVICE.h"
#include <Wire.h>

class MP_PAH8001EI2G_Seeed
{
public:
  MP_PAH8001EI2G_Seeed();
  int init();
  void update(unsigned long current_time);
  void printStatus();

  double getHeart_Rate();

private:
  double heartRate = 0;
  unsigned long lastMillis = 0;
};

#endif
