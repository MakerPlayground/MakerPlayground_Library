#ifndef VD_TIMER_H
#define VD_TIMER_H

#include <Arduino.h>

class VD_TIMER
{
public:
	VD_TIMER();
	int init();
	void update(unsigned long time);
	void printStatus();
	static const char* const* ERRORS;

	int getSecond();
	void startTimer();
	void stopTimer();
	bool isOverTime(int second);

private:
	int second;
	unsigned long start;
	bool isStarted;
};

#endif
