#ifndef MP_NETPIE_VIRTUAL_SLIDER_H
#define MP_NETPIE_VIRTUAL_SLIDER_H

#include "MP_DEVICE.h"
#include "MP_NETPIE.h"

class MP_NETPIE_VIRTUAL_SLIDER
{
public:
    MP_NETPIE_VIRTUAL_SLIDER(char* topic, MP_NETPIE* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();
    static const char* const* ERRORS;

    double getValue();
private:
    char* topic;
    MP_NETPIE* netpie;
    double value = 0.0;
};

#endif 