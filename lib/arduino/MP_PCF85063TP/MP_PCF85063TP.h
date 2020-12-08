#ifndef MP_PCF85063TP_H
#define MP_PCF85063TP_H

#include "Arduino.h"
#include "MP_DEVICE.h"

#include <Wire.h> // must be included here so that Arduino library object file references work
#include <PCF85063TP.h>

class MP_PCF85063TP {
public:
    MP_PCF85063TP();
	int init();
	void update(unsigned long current_time);
	void printStatus();
    
    void setDateTime(const char* date_time);
    bool checkDayOfWeek(uint8_t day);
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();
    uint8_t getDate();
    uint8_t getMonth();
    uint16_t getYear();

private:
    PCD85063TP RTclock;
    
    unsigned long lastMillis = 0;
    // uint8_t second, minute, hour, dayOfWeek, dayOfMonth, month;
    // uint16_t year;
    bool isValid = false;
};

#endif