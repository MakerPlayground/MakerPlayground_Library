#ifndef MP_BLYNK_NOTIFICATION_H
#define MP_BLYNK_NOTIFICATION_H

#include "MP_DEVICE.h"
#include "MP_BLYNK.h"

class MP_BLYNK_NOTIFICATION 
{
public:
    MP_BLYNK_NOTIFICATION(MP_BLYNK* blynk);
    int init();
    void update(unsigned long current_time);
    void printStatus();

    void notify(char* msg);

private:
    MP_BLYNK* blynk;
};

#endif