#ifndef MP_AHT20_H
#define MP_AHT20_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <Adafruit_AHTX0.h>

class MP_AHT20
{
public:
    MP_AHT20();

    int init();
    void update(unsigned long current_time);
    void printStatus();

    double getTemperature();
    double getHumidity();

private:
    Adafruit_AHTX0 aht;
    uint8_t pin;

    double temp;
    double humid;
    bool isValid;
    unsigned long last_update = 0;
};

#endif
