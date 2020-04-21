#ifndef MP_NETPIE2020_VIRTUAL_GAUGE_H
#define MP_NETPIE2020_VIRTUAL_GAUGE_H

#include "MP_DEVICE.h"
#include "MP_NETPIE2020.h"

class MP_NETPIE2020_VIRTUAL_GAUGE
{
public:
    MP_NETPIE2020_VIRTUAL_GAUGE(char* topic, MP_NETPIE2020* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();

    void setNumber(double value);

private:
    char* topic;
    MP_NETPIE2020* netpie;
    double current_value;
};

#endif 