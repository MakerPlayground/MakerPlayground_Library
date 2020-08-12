#ifndef ESP32_POLYFILL_H
#define ESP32_POLYFILL_H

#ifdef ESP32
#include <Arduino.h>

uint8_t getChannel(uint8_t pin);
void analogWrite(uint8_t pin, uint16_t value);
void tone(uint8_t pin, uint16_t freq);
void noTone(uint8_t pin);
#endif

#endif