#ifndef MP_BLYNK_WIDGET_MAP_H
#define MP_BLYNK_WIDGET_MAP_H

#include "MP_DEVICE.h"
#include "MP_BLYNK.h"

class MP_BLYNK_WIDGET_MAP 
{
public:
    MP_BLYNK_WIDGET_MAP(uint8_t v_pin, uint8_t pinIndex, MP_BLYNK* blynk);
    int init();
    void update(unsigned long current_time);
    void printStatus();

    void pinLocation(double latitude, double longitude);
    void clearPin();

private:
    unsigned long lastSentMillis = 0;
    uint8_t v_pin;
    uint8_t pinIndex;
    MP_BLYNK* blynk;
    double lat = 0.0;
    double lon = 0.0;
    bool clearPinSentRequest = false;
};

#endif