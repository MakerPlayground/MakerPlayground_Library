#ifndef MP_IKB_1_H
#define MP_IKB_1_H

#include "MP_DEVICE.h"
#include <Wire.h>

#define IKB1_I2C_ADDR 0x48
#define IKB1_MODE_OUTPUT 0x01
#define IKB1_MODE_INPUT 0x02

class MP_IKB_1
{
public:

	MP_IKB_1();
	int init();
	void update(unsigned long current_time);
	void printStatus();

    void digitalOut(uint8_t pin, uint8_t logic);
    bool isHigh(uint8_t pin);
    bool isLow(uint8_t pin);
    
    double getA0_Percent();
    double getA1_Percent();
    double getA2_Percent();
    double getA3_Percent();
    double getA4_Percent();
    double getA5_Percent();
    double getA6_Percent();
    double getA7_Percent();

private:
    double getA_Percent(uint8_t pin);
    double getValue(uint8_t pin);
    uint8_t modes[8] = {0};
    uint8_t values[8] = {0};
    unsigned long nextReading = 0;
};
#endif
