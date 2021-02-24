#ifndef MP_PCF8574_KEYPAD_H
#define MP_PCF8574_KEYPAD_H

#include "Arduino.h"
#include "MP_DEVICE.h"

#include <Keypad.h>        // GDY120705
#include <Keypad_I2C.h>
#include <Wire.h>

class MP_PCF8574_Keypad {
public:
    MP_PCF8574_Keypad(uint8_t a0_reg, uint8_t a1_reg, uint8_t a2_reg);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    bool foundCharacter(char * character);
    bool foundNumber();
    bool foundNothing();

    uint8_t getNumber();

private:
    unsigned long lastMillis = 0;
    #define ROWS 4
    #define COLS 4
    //define the cymbols on the buttons of the keypads
    const char hexaKeys[ROWS][COLS] = {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'*','0','#','D'}
    };
    byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
    byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

    //Initialisierung von Keypad
    bool hasKey = false;
    bool hasChar = false;
    bool hasNum = false;
    uint8_t numValue = 0;
    char charValue = '\0';

    uint8_t addr = 0x38;
    Keypad_I2C i2cKeypad;
};

#endif