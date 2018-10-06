#ifndef MP_NETPIE_VIRTUALGAUGE
#define MP_NETPIE_VIRTUALGAUGE

#include <Arduino.h>
#include "MP_Netpie_ESP8266.h"

class MP_Netpie_VirtualGauge
{
public:
    MP_Netpie_VirtualGauge(char* topic, MP_Netpie_ESP8266* netpie);

    int init();
    void update(unsigned long time);

    void setNumber(double value);

private:
    char* topic;
    MP_Netpie_ESP8266* netpie;
};

#endif 