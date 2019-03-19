#ifndef VD_TIMER_H
#define VD_TIMER_H

#include "MP_DEVICE.h"

class VD_TIMER
{
public:
	VD_TIMER();
	int init();
	void update(unsigned long time);
	void printStatus();

	int getSecond();
	void startTimer();
	void stopTimer();
	bool isOverTime(int second);
	bool isNotOverTime(int second);

private:
	int second;
	unsigned long start;
	bool isStarted;
};

#endif
