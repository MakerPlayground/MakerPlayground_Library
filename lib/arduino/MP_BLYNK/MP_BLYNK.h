#ifndef MP_BLYNK_H
#define MP_BLYNK_H


class MP_BLYNK 
{
public:
	virtual int init() = 0;
	virtual void update(unsigned long current_time) = 0;
	virtual void printStatus() = 0;

	virtual bool isReady() = 0;
	virtual int readVirtualPin(uint8_t pin) = 0;   // pin = 0-7
	virtual void writeVirtualPin(uint8_t pin, double value) = 0;   // pin = 0-7
    virtual void writeVirtualPin(uint8_t pin, int val1, double val2, double val3, char* val4) = 0;
    virtual void writeVirtualPin(uint8_t pin, char* val1) = 0;
	virtual void notify(const char* msg) = 0;
	
	// high level function use by maker playground
	virtual bool checkVirtualPinValue(uint8_t pin, int value) = 0;
	virtual int getVirtualPin0() = 0;
	virtual int getVirtualPin1() = 0;
	virtual int getVirtualPin2() = 0;
	virtual int getVirtualPin3() = 0;
	virtual int getVirtualPin4() = 0;
	virtual int getVirtualPin5() = 0;
	virtual int getVirtualPin6() = 0;
	virtual int getVirtualPin7() = 0;
};

#endif