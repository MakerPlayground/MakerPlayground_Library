#ifndef VD_STATISTIC_H
#define VD_STATISTIC_H

#include "MP_DEVICE.h"

class VD_STATISTIC
{
public:
	VD_STATISTIC();
	int init();
	void update(unsigned long time);
	void printStatus();
	static const char* const* ERRORS;

	void addData(double value);
	unsigned long getCount();
	double getAverage();
	double getSD();
	double getVariance();

private:
	unsigned long N = 0;
	double sum = 0.0;
	double sum_sq = 0.0;

	double average;
	double variance;
	double SD;
};

#endif
