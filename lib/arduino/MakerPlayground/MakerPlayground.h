#ifndef MAKERPLAYGROUND_H
#define MAKERPLAYGROUND_H

#include <Arduino.h>
#include "MP_ERROR.h"

/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define MPSerial SerialUSB
#else
  #define MPSerial Serial
#endif

#define PR_DEVICE(device) MPSerial.print("\""); MPSerial.print(device); MPSerial.print("\""); MPSerial.write('\0');
#define PR_INFO(device) MPSerial.print(F("[[I]]")); MPSerial.write('\0'); PR_DEVICE(device);
#define PR_ERR(device) MPSerial.print(F("[[E]]")); MPSerial.write('\0'); PR_DEVICE(device);
#define PR_VAL(device) MPSerial.print(F("[[V]]")); MPSerial.write('\0'); PR_DEVICE(device);
#define PR_END() MPSerial.println('\0')

#define MP_LOG_INTERVAL 1000
#define MP_LOG(device, name) PR_INFO(F(name)); device.printStatus(); PR_END(); 
#define MP_LOG_P(device, name) PR_INFO(F(name)); device->printStatus(); PR_END();
#ifdef __AVR__
    #define MP_ERR(name, status_code) PR_ERR(F(name)); MPSerial.println(reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(&(ERRORS[status_code])))); PR_END();
#else
    #define MP_ERR(name, status_code) PR_ERR(F(name)); MPSerial.println(reinterpret_cast<const __FlashStringHelper *>(ERRORS[status_code])); PR_END();
#endif

//typedef void (*Task)(void);
//struct Expr {
//    double (*fn)(void) = NULL;
//    double value = 0.0;
//    unsigned int interval = 0;
//    unsigned long latestUpdateTime = 0;
//};

uint8_t status_code = 0;
unsigned long currentTime = 0;
unsigned long latestLogTime = 0;

void update();

//void evaluateExpression(Task task, Expr expr[], int numExpr) {
//    if (task != NULL) {
//        for (int i=0; i<numExpr; i++) {
//            if (expr[i].fn != NULL && currentTime - expr[i].latestUpdateTime >= expr[i].interval) {
//                expr[i].value = expr[i].fn();
//                expr[i].latestUpdateTime = currentTime;
//                task();
//            }
//        }
//    }
//}
//
//void setExpression(Expr& expr, double (*fn)(void), unsigned int interval) {
//    expr.fn = fn;
//    expr.value = fn();
//    expr.interval = interval;
//    expr.latestUpdateTime = currentTime;
//}
//
//void clearExpression(Expr& expr) {
//    expr.fn = NULL;
//}
//
//void setTask(Task& task, void (*fn)(void)) {
//    task = fn;
//    task();
//}

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif