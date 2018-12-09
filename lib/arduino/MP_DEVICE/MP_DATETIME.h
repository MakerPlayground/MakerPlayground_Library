#ifndef MP_DATETIME_H
#define MP_DATETIME_H

#include "Arduino.h"

class MP_DATETIME {
public:
    MP_DATETIME(uint8_t second, uint8_t minute, uint8_t hour, uint8_t date, uint8_t month, uint16_t year) {
        ss = second;
        mm = minute;
        hh = hour;
        DD = date;
        MM = month;
        YY = year;
    }

    uint8_t getSecond() {
        return ss;
    }

    uint8_t getMinute() {
        return mm;
    }

    uint8_t getHour() {
        return hh;
    }

    uint8_t getDate() {
        return DD;
    }

    uint8_t getMonth() {
        return MM;
    }

    uint8_t getYear() {
        return YY;
    }

    // 1-7 <=> Sun-Sat
    uint8_t getDayOfWeek() {
        return dayofweek(DD, MM, YY);
    }

private:
    uint8_t ss;         // 0-59
    uint8_t mm;         // 0-59
    uint8_t hh;         // 0-23
    uint8_t DD;         // 1-31
    uint8_t MM;         // 1-12
    uint16_t YY;        // 0-now

    // Modified from https://www.geeksforgeeks.org/find-day-of-the-week-for-a-given-date/
    uint8_t dayofweek(int d, int m, int y)
    {
        static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
        y -= (m < 3) ? 1 : 0;
        return (( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7) + 1; 
    } 
};

#endif