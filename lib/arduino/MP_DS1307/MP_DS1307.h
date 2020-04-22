#ifndef MP_DS1307_H
#define MP_DS1307_H

#include "Arduino.h"
#include "MP_DEVICE.h"
// CONNECTIONS:
// DS3231 SDA --> SDA
// DS3231 SCL --> SCL
// DS3231 VCC --> 3.3v or 5v
// DS3231 GND --> GND

/* for software wire use below
#include <SoftwareWire.h>  // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>

SoftwareWire myWire(SDA, SCL);
RtcDS3231<SoftwareWire> Rtc(myWire);
 for software wire use above */

/* for normal hardware wire use below */
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
/* for normal hardware wire use above */

class MP_DS1307 {
public:
    MP_DS1307();
	int init();
	void update(unsigned long current_time);
	void printStatus();
    
    void setDateTime(MP_DATETIME datetime);
    bool checkDayOfWeek(uint8_t day);
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();
    uint8_t getDate();
    uint8_t getMonth();
    uint16_t getYear();

private:
    RtcDateTime now;
    RtcDS1307<TwoWire> Rtc;
    unsigned long lastMillis = 0;
    // uint8_t second, minute, hour, dayOfWeek, dayOfMonth, month;
    // uint16_t year;
    bool isValid = false;
};

#endif