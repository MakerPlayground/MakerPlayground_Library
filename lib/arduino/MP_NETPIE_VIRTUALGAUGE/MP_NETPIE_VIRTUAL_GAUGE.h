#ifndef MP_NETPIE_VIRTUAL_GAUGE
#define MP_NETPIE_VIRTUAL_GAUGE

#include <Arduino.h>
#include "MP_NETPIE.h"

class MP_NETPIE_VIRTUAL_GAUGE
{
public:
    MP_NETPIE_VIRTUAL_GAUGE(char* topic, MP_NETPIE* netpie);

    int init();
    void update(unsigned long time);

    void setNumber(double value);

private:
    char* topic;
    MP_NETPIE* netpie;
};

#endif 