#ifndef MAKERPLAYGROUND_H
#define MAKERPLAYGROUND_H

#include <Arduino.h>
#include "MP_ERROR.h"

#define MP_LOG_INTERVAL 1000
#define MP_LOG(device, name) Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] ")); device.printStatus(); Serial.println('\0');
#ifdef __AVR__
    #define MP_ERR(name, status_code) Serial.print(F("[[ERROR]] ")); Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] ")); Serial.println(reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(&(ERRORS[status_code])))); Serial.println('\0');
#else
    #define MP_ERR(name, status_code) Serial.print(F("[[ERROR]] ")); Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] ")); Serial.println(reinterpret_cast<const __FlashStringHelper *>(ERRORS[status_code])); Serial.println('\0');
#endif
#define MP_LOG_P(device, name) Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] ")); device->printStatus(); Serial.println('\0');

typedef void (*Task)(void);
struct Expr {
    double (*fn)(void) = NULL;
    double value = 0.0;
    unsigned int interval = 0;
    unsigned long latestUpdateTime = 0;
};

void (*currentNode)(void);
uint8_t status_code = 0;
unsigned long currentTime = 0;
unsigned long latestLogTime = 0;

void update();

void evaluateExpression(Task task, Expr expr[], int numExpr) {
    if (task != NULL) {
        for (int i=0; i<numExpr; i++) {
            if (expr[i].fn != NULL && currentTime - expr[i].latestUpdateTime >= expr[i].interval) {
                expr[i].value = expr[i].fn();
                expr[i].latestUpdateTime = currentTime;
                task();
            }
        }
    }
}

void setExpression(Expr& expr, double (*fn)(void), unsigned int interval) {
    expr.fn = fn;
    expr.value = fn();
    expr.interval = interval;
    expr.latestUpdateTime = currentTime;
}

void clearExpression(Expr& expr) {
    expr.fn = NULL;
}

void setTask(Task& task, void (*fn)(void)) {
    task = fn;
    task();
}

double map(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif