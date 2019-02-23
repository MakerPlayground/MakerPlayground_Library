#ifndef MP_SHARP_GP2D120X
#define MP_SHARP_GP2D120X

#include "MP_DEVICE.h"

class MP_SHARP_GP2D120X
{
public:
    MP_SHARP_GP2D120X(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

    double getDistance();

private:
    uint8_t pin;
    double cm;
};

#endif