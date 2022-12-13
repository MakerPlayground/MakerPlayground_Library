#ifndef MP_REST_MPBASEBOARD_H
#define MP_REST_MPBASEBOARD_H

#include <Arduino.h>
#include "MP_DEVICE.h"
#include "MP_REST.h"

class MP_REST_MPBASEBOARD : public MP_REST
{
public:
    MP_REST_MPBASEBOARD(const char* ssid, const char* pass);
    int init();
	void update(unsigned long currentTime);
	void printStatus();

    bool isConnected();

private:
    bool checkResponse();

    const char* ssid;
    const char* pass;
};

#endif