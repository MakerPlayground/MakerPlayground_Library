#ifndef MP_NETPIE_NOTIFICATION_H
#define MP_NETPIE_NOTIFICATION_H

#include "MP_DEVICE.h"
#include "MP_NETPIE.h"

class MP_NETPIE_NOTIFICATION 
{
public:
    MP_NETPIE_NOTIFICATION(MP_NETPIE* netpie);
    int init();
    void update(unsigned long current_time);
    void printStatus();

    void notify(char* msg);

private:
    MP_NETPIE* netpie;
};

#endif