#ifndef MP_MAX30100_H
#define MP_MAX30100_H

#include "Arduino.h"
#include "MP_DEVICE.h"
#include "MAX30100_PulseOximeter.h"

class MP_MAX30100 {
public:
  MP_MAX30100();
  int init();
  void update(unsigned long current_time);
  void printStatus();

  float getHeart_Rate();
  uint8_t getSpO2();

private:
  PulseOximeter pox;
  float hr = 0;
  uint8_t spo2 = 0;
  unsigned long lastMillis = 0;
};

#endif