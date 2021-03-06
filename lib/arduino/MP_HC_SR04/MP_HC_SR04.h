#ifndef MP_HC_SR04_H
#define MP_HC_SR04_H

#include "MP_DEVICE.h"
#include <NewPing.h>

class MP_HC_SR04
{
public:
    MP_HC_SR04(uint8_t trig ,uint8_t echo);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    double getDistance();

private:
    uint8_t trig;
    uint8_t echo;
    double cm;
    unsigned long nextReading;
    NewPing sonar;
};

#endif