#ifndef MP_BLYNK_VIRTUAL_BUTTON_H
#define MP_BLYNK_VIRTUAL_BUTTON_H

#include "MP_DEVICE.h"
#include "MP_BLYNK.h"

class MP_BLYNK_VIRTUAL_BUTTON 
{
public:
    MP_BLYNK_VIRTUAL_BUTTON(uint8_t v_pin, MP_BLYNK* blynk);
    int init();
    void update(unsigned long current_time);
    void printStatus();
    
    bool isPress();
    bool isPressAndRelease();
    bool isNotPress();

private:
    uint8_t v_pin;
    MP_BLYNK* blynk;
	unsigned long checkpoint = 0;
    bool bPress = false;
    enum ButtonState { NOTHING, PRESSED, JUST_RELEASE };
	ButtonState state = NOTHING;
};

#endif