#ifndef MP_IKB_1_H
#define MP_IKB_1_H

#include "MP_DEVICE.h"
#include <Wire.h>

#define IKB1_I2C_ADDR 0x48
#define IKB1_INPUT_ONLY 0x00
#define IKB1_OUTPUT_ONLY 0x01
#define IKB1_BOTH 0x02
#define IKB1_MOTOR_FORWARD 1
#define IKB1_MOTOR_BACKWARD 0

class MP_IKB_1
{
public:

	MP_IKB_1(uint8_t mode0, uint8_t mode1, uint8_t mode2, uint8_t mode3, uint8_t mode4, uint8_t mode5, uint8_t mode6, uint8_t mode7);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    /* GPIO */
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

    /* Servo */
    void moveServo(uint8_t channel, int degree);
    void freeServo(uint8_t channel);

    /* DC Motor */
    void motorOn(uint8_t channel, int direction, int percent);
    void motorOff(uint8_t channel);

private:
    double getA_Percent(uint8_t pin);
    double getValue(uint8_t pin);
    uint8_t modes[8] = {0};
    uint8_t values[8] = {0};
    unsigned long nextReading = 0;
};
#endif
