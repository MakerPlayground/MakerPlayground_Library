#ifndef ESP32_POLYFILL_H
#define ESP32_POLYFILL_H

#ifdef ESP32
#include <Arduino.h>

void analogWrite(uint8_t pin, uint16_t value);
void tone(uint8_t pin, uint16_t freq);
void noTone(uint8_t pin);
#endif

#endif