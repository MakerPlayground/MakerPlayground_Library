#ifndef MP_NTP_MPBASEBOARD_H
#define MP_NTP_MPBASEBOARD_H

#include "MP_DEVICE.h"
#include "MP_REST.h"

class MP_NTP_MPBASEBOARD {
public:
    MP_NTP_MPBASEBOARD();
	int init();
	void update(unsigned long current_time);
	void printStatus();

    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();
    uint8_t getDate();
    uint8_t getMonth();
    uint16_t getYear();

private:
    bool checkResponse();

    unsigned long lastMillis = 0;
    byte second, minute, hour, date, month, year;
};

#endif