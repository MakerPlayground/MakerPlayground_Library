#ifndef MP_BLYNK_VIRTUAL_SLIDER_H
#define MP_BLYNK_VIRTUAL_SLIDER_H

#include "MP_DEVICE.h"
#include "MP_BLYNK.h"

class MP_BLYNK_VIRTUAL_SLIDER 
{
public:
    MP_BLYNK_VIRTUAL_SLIDER(uint8_t v_pin, MP_BLYNK* blynk);
    int init();
    void update(unsigned long current_time);
    void printStatus();
    static const char* const* ERRORS;

    double getValue();

private:
    uint8_t v_pin;
    MP_BLYNK* blynk;
    double value = 0.0;
};

#endif