#ifndef MP_NETPIE2020_VIRTUAL_SLIDER_H
#define MP_NETPIE2020_VIRTUAL_SLIDER_H

#include "MP_DEVICE.h"
#include "MP_NETPIE2020.h"

class MP_NETPIE2020_VIRTUAL_SLIDER
{
public:
    MP_NETPIE2020_VIRTUAL_SLIDER(char* topic, MP_NETPIE2020* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();

    double getValue();
private:
    char* topic;
    MP_NETPIE2020* netpie;
    double value = 0.0;
};

#endif 