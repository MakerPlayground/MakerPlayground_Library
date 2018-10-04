#ifndef MP_BLYNK_H
#define MP_BLYNK_H

#include <Arduino.h>

class MP_BLYNK 
{
public:
	virtual int init();
	virtual void update(unsigned long current_time);
	virtual void printStatus();
	static const char* const* ERRORS;

	virtual bool isReady();
	virtual int readVirtualPin(uint8_t pin);   // pin = 0-7
	virtual void writeVirtualPin(char pin[], double value);   // pin = 0-7

	// high level function use by maker playground
	virtual bool checkVirtualPinValue(char pin[], int value);
	virtual int getVirtualPin0();
	virtual int getVirtualPin1();
	virtual int getVirtualPin2();
	virtual int getVirtualPin3();
	virtual int getVirtualPin4();
	virtual int getVirtualPin5();
	virtual int getVirtualPin6();
	virtual int getVirtualPin7();
};

#endif