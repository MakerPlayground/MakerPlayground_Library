#include "MP_ADXL345.h"

MP_ADXL345::MP_ADXL345()
{
}

int MP_ADXL345::init()
{
	accel = Adafruit_ADXL345_Unified(12345);
	/* Initialise the sensor */
	if(!accel.begin())
	{
		return ERR_CONNECT_DEVICE;
	}

	/* Set the range to whatever is appropriate for your project */
	// accel.setRange(ADXL345_RANGE_16_G);
	// displaySetRange(ADXL345_RANGE_8_G);
	// displaySetRange(ADXL345_RANGE_4_G);
	accel.setRange(ADXL345_RANGE_2_G);
	
	/* Display some basic information on this sensor */
	// displaySensorDetails();
	
	// /* Display additional settings (outside the scope of sensor_t) */
	// displayDataRate();
	// displayRange();
	old_time = 0;
	return ERR_OK;
}

void MP_ADXL345::update(unsigned long current_time)
{
	if (current_time - old_time > 200) 
	{
		accel.getEvent(&event);
		double acc_x = event.acceleration.x;
		double acc_y = event.acceleration.y;
		double acc_z = event.acceleration.z;
		acc_mag = sqrt(acc_x*acc_x + acc_y*acc_y + acc_z*acc_z);
		old_time = current_time;
	}
}

void MP_ADXL345::printStatus()
{
	Serial.print(F("accel_x = "));
	Serial.println(event.acceleration.x);

	Serial.print(F("accel_y = "));
	Serial.println(event.acceleration.y);
	
	Serial.print(F("accel_z = "));
	Serial.println(event.acceleration.z);
	
	Serial.print(F("accel_magnitude = "));
	Serial.println(acc_mag);
}

double MP_ADXL345::getAccel_X()
{
	return event.acceleration.x;
}

double MP_ADXL345::getAccel_Y()
{
	return event.acceleration.y;
}

double MP_ADXL345::getAccel_Z()
{
	return event.acceleration.z;
}

double MP_ADXL345::getAccel_Magnitude()
{
	return acc_mag;
}
