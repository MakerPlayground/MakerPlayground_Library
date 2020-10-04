#ifndef MP_BMM150_H
#define MP_BMM150_H

#include "MP_DEVICE.h"
#include "bmm150.h"
#include "bmm150_defs.h"

class MP_BMM150
{
public:
	MP_BMM150();
	int init();
	void update(unsigned long current_time);
	void printStatus();

  double getMag_X();
  double getMag_Y();
  double getMag_Z();
  double getHeading();
  
  bool checkDirection(int dir);

private:
	BMM150 bmm = BMM150();
	unsigned long end_time;
  bmm150_mag_data value;
	float headingDegrees;
};

#endif
