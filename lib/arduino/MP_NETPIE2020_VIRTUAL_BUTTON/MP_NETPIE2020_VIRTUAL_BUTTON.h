#ifndef MP_NETPIE2020_VIRTUAL_BUTTON_H
#define MP_NETPIE2020_VIRTUAL_BUTTON_H

#include "MP_DEVICE.h"
#include "MP_NETPIE2020.h"

class MP_NETPIE2020_VIRTUAL_BUTTON
{
public:
    MP_NETPIE2020_VIRTUAL_BUTTON(char* topic, MP_NETPIE2020* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();

    bool isPress();
    bool isNotPress();
    bool isPressAndRelease();

private:
    char* topic;
    MP_NETPIE2020* netpie;
    unsigned long checkpoint = 0;
    bool bPress = false;
    enum ButtonState { NOTHING, PRESSED, JUST_RELEASE };
	ButtonState state = NOTHING;
};

#endif 