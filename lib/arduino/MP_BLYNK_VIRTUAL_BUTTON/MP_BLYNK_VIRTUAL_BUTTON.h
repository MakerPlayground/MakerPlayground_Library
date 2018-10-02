#ifndef MP_BLYNK_VIRTUAL_BUTTON_H
#define MP_BLYNK_VIRTUAL_BUTTON_H

class MP_BLYNK_VIRTUAL_BUTTON 
{
public:
    MP_BLYNK_VIRTUAL_BUTTON(uint8_t v_pin);
    int init();
    void update(unsigned long current_time);
    void printStatus();
    static const char* const* ERRORS;

    bool isPress();
    bool isPressAndRelease();
    bool isNotPress();

private:
    uint8_t v_pin;
};

#endif