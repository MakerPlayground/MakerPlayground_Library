#ifndef MP_NETPIE2020_VIRTUAL_LED_H
#define MP_NETPIE2020_VIRTUAL_LED_H

#include "MP_DEVICE.h"
#include "MP_NETPIE2020.h"

class MP_NETPIE2020_VIRTUAL_LED
{
public:
    MP_NETPIE2020_VIRTUAL_LED(char* topic, MP_NETPIE2020* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();

    void on();
    void off();

private:
    char* topic;
    MP_NETPIE2020* netpie;
    bool ledStatus;
};

#endif 