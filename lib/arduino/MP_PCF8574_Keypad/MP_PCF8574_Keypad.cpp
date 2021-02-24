#include "MP_PCF8574_Keypad.h"

#define REFRESH_INTERVAL 50

MP_PCF8574_Keypad::MP_PCF8574_Keypad(uint8_t a0_reg, uint8_t a1_reg, uint8_t a2_reg)
    : addr(0x38 + a0_reg + (a1_reg >> 1) + (a2_reg >> 2))
    , i2cKeypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, addr)
{

}

int MP_PCF8574_Keypad::init() {
    i2cKeypad.begin( makeKeymap(hexaKeys) );
    return MP_ERR_OK;
}

bool MP_PCF8574_Keypad::foundCharacter(char * character) {
    return hasChar && (character[0] == charValue);
}

bool MP_PCF8574_Keypad::foundNumber() {
    return hasNum;
}

bool MP_PCF8574_Keypad::foundNothing() {
    return !hasKey;
}

uint8_t MP_PCF8574_Keypad::getNumber() {
    hasKey = false;
    hasNum = false;
    return numValue;
}

void MP_PCF8574_Keypad::update(unsigned long current_time) {
    if (current_time - lastMillis >= REFRESH_INTERVAL) {
        char key = i2cKeypad.getKey();
        hasChar = false;
        hasNum = false;
        if (key && '0' <= key && key <= '9') {
            hasKey = true;
            hasNum = true;
            numValue = (key - '0');
        } else if (key) {
            hasKey = true;
            hasChar = true;
            charValue = key;
        } else {
            hasKey = false;
        }
        lastMillis = current_time;
    }
}

void MP_PCF8574_Keypad::printStatus() 
{

}