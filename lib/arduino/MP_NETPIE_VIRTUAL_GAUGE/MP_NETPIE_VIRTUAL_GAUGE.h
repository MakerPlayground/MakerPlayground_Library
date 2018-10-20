#ifndef MP_NETPIE_VIRTUAL_GAUGE_H
#define MP_NETPIE_VIRTUAL_GAUGE_H

#include "MP_DEVICE.h"
#include "MP_NETPIE.h"

class MP_NETPIE_VIRTUAL_GAUGE
{
public:
    MP_NETPIE_VIRTUAL_GAUGE(char* topic, MP_NETPIE* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();
    static const char* const* ERRORS;

    void setNumber(double value);

private:
    char* topic;
    MP_NETPIE* netpie;
    double current_value;
};

#endif 