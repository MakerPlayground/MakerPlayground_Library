#ifndef MP_REST_WIOTERMINAL_H
#define MP_REST_WIOTERMINAL_H

#include "MP_DEVICE.h"
#include "MP_REST.h"

class MP_REST_WIOTERMINAL : public MP_REST
{
public:
    MP_REST_WIOTERMINAL(const char* ssid, const char* pass);
    int init();
	void update(unsigned long currentTime);
	void printStatus();

    bool isConnected();

private:
    const char* ssid;
    const char* pass;
};

#endif