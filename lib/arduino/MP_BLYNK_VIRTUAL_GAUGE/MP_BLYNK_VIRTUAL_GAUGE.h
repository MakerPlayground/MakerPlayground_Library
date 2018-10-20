#ifndef MP_BLYNK_VIRTUAL_GAUGE_H
#define MP_BLYNK_VIRTUAL_GAUGE_H

#include "MP_DEVICE.h"
#include "MP_BLYNK.h"

class MP_BLYNK_VIRTUAL_GAUGE 
{
public:
    MP_BLYNK_VIRTUAL_GAUGE(uint8_t v_pin, MP_BLYNK* blynk);
    int init();
    void update(unsigned long current_time);
    void printStatus();
    static const char* const* ERRORS;

    void setNumber(double value);

private:
    uint8_t v_pin;
    MP_BLYNK* blynk;
    double value = 0.0;
};

#endif