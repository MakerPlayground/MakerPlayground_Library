#ifndef MP_NETPIE_VIRTUAL_BUTTON_H
#define MP_NETPIE_VIRTUAL_BUTTON_H

#include "MP_DEVICE.h"
#include "MP_NETPIE.h"

class MP_NETPIE_VIRTUAL_BUTTON
{
public:
    MP_NETPIE_VIRTUAL_BUTTON(char* topic, MP_NETPIE* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();

    bool isPress();
    bool isNotPress();
    bool isPressAndRelease();

private:
    char* topic;
    MP_NETPIE* netpie;
    bool bPress = false;
};

#endif 