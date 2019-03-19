#ifndef MP_RTC_MCP4971X_H
#define MP_RTC_MCP4971X_H

#include "Arduino.h"
#include "MP_DEVICE.h"

#include "MCP7941x.h"   // The implementation of the MCP7941x might varying to the library_dependency 
                        // such as for KidBright V1.3 which use I2C1 instead of default I2C.
                        // For this reason, be aware of using two devices for both I2C and I2C1 since we
                        // do not separate MP_RTC_MCP4971X class for the different implementations.

class MP_RTC_MCP4971x {
public:
    MP_RTC_MCP4971x();
	int init();
	void update(unsigned long current_time);
	void printStatus();

    void setDateTime(MP_DATETIME datetime);
    bool checkDayOfWeek(char* dayName);
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();
    uint8_t getDate();
    uint8_t getMonth();
    uint16_t getYear();

private:
    MCP7941x rtc;
    unsigned long lastMillis = 0;
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
};

#endif