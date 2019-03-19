#ifndef MP_NETPIE_VIRTUAL_LED_H
#define MP_NETPIE_VIRTUAL_LED_H

#include "MP_DEVICE.h"
#include "MP_NETPIE.h"

class MP_NETPIE_VIRTUAL_LED
{
public:
    MP_NETPIE_VIRTUAL_LED(char* topic, MP_NETPIE* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();

    void on();
    void off();

private:
    char* topic;
    MP_NETPIE* netpie;
    bool ledStatus;
};

#endif 