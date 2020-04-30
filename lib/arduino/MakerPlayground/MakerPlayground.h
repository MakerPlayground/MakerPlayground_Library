#ifndef MAKERPLAYGROUND_H
#define MAKERPLAYGROUND_H

#include <Arduino.h>
#include "MP_ERROR.h"

#define PR_INFO(device) Serial.print(F("[[I]] \"")); Serial.print(device); Serial.print("\" ");
#define PR_ERR(device) Serial.print(F("[[E]] \"")); Serial.print(device); Serial.print("\" ");
#define PR_VAL(device) Serial.print(F("[[V]] \"")); Serial.print(device); Serial.print("\" ");
#define PR_DEVICE(device) Serial.print("\""); Serial.print(device); Serial.print("\" ");
#define PR_END() Serial.println(F("\0"))

#define MP_LOG_INTERVAL 1000
#define MP_LOG(device, name) PR_INFO(F(name)); device.printStatus(); PR_END(); 
#define MP_LOG_P(device, name) PR_INFO(F(name)); device->printStatus(); PR_END();
#ifdef __AVR__
    #define MP_ERR(name, status_code) PR_ERR(F(name)); Serial.println(reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(&(ERRORS[status_code])))); PR_END();
#else
    #define MP_ERR(name, status_code) PR_ERR(F(name)); Serial.println(reinterpret_cast<const __FlashStringHelper *>(ERRORS[status_code])); PR_END();
#endif

uint8_t status_code = 0;
unsigned long currentTime = 0;
unsigned long latestLogTime = 0;

void update();

double map(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

typedef void (*Task)(double);

// easing function

double Linear(double d) {
    return d;
}

double EaseInExpo(double d) {
    return d == 0 ? 0 : pow(2, 10 * d - 10);
}

template<int c1x, int c1y, int c2x, int c2y>
double bezierCurve(double d) {
    double p1x, p1y, p2x, p2y, p3x, p3y;
    p1x = d * (c1x/100.0);
    p1y = d * (c1y/100.0);
    p2x = (1.0-d) * (c1x/100.0) + d * (c2x/100.0);
    p2y = (1.0-d) * (c1y/100.0) + d * (c2y/100.0);
    p3x = (1.0-d) * (c2x/100.0) + d;
    p3y = (1.0-d) * (c2y/100.0) + d;

    p1x = (1.0-d) * p1x + d * p2x;
    p1y = (1.0-d) * p1y + d * p2y;
    p2x = (1.0-d) * p2x + d * p3x;
    p2y = (1.0-d) * p2y + d * p3y;

    p1x = (1.0-d) * p1x + d * p2x;
    p1y = (1.0-d) * p1y + d * p2y;
    return p1y;
}

template <class T>
class ValueAnimator {
public:
    T getValue(unsigned long currentTime) const {
        return easing(constrain((double) (currentTime - startTime) / duration, 0.0, 1.0)) * (endValue - startValue) + startValue;
    }

    double (*easing)(double);
    T startValue;
    T endValue;
    unsigned long duration;
    unsigned long startTime;
};

template <int size>
class NumericValueLookup{
public:
    double getValue(unsigned long currentTime) {
        unsigned long period = currentTime - startTime;
        int i;
        for (i=count-1; i>0; i--) { // use > 0 so that i is clipped to 0 when period is invalid
            if (time[i] < period) {
                break;
            }
        }
        return value[i];
    }

    double value[size];
    unsigned long time[size];
    int count;
    unsigned long startTime;
};

const int BUFFER_SIZE 64;
char buffer[BUFFER_SIZE];

template <int size>
class StringValueLookup{
public:
    char* getValue(char* buffer, unsigned long currentTime) const {
        unsigned long period = currentTime - startTime;
        int i;
        for (i=count-1; i>0; i--) { // use > 0 so that i is clipped to 0 when period is invalid
            if (time[i] < period) {
                break;
            }
        }

        const char* s = (char *) pgm_read_word(&(value[i]));
        char* ptr = buffer;

        char c;
        while ((c = pgm_read_byte(s)) != '\0') {
            if (c == '%') {
                s++;
                c = pgm_read_byte(s);
                if (c == '%') {
                    *ptr = c;
                    ptr++;
                } else {
                    dtostrf(arg[c - '0'], 1, 2, ptr);
                    while (*ptr != '\0')
                        ptr++;
                }
            } else {
                *ptr = c;
                ptr++;
            }
            s++;
        }
        *ptr = '\0';
        return buffer;
    }

    const char* const* value;
    unsigned long time[size];
    double arg[size];
    int count;
    unsigned long startTime;
};

#endif