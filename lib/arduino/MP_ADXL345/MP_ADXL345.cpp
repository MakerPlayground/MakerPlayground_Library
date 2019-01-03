#include "MP_ADXL345.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "No ADXL345 detected ... Check your wiring!";
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_ADXL345::ERRORS = errors_p;

MP_ADXL345::MP_ADXL345()
{
}

int MP_ADXL345::init()
{
	accel = Adafruit_ADXL345_Unified(12345);
	/* Initialise the sensor */
	if(!accel.begin())
	{
		return 1;
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
	return 0;
}

void MP_ADXL345::update(unsigned long current_time)
{
	if (current_time - old_time > 200) 
	{
		accel.getEvent(&event);
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
	Serial.println(this->getAccel_Magnitude());
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
	double acc_x = event.acceleration.x;
	double acc_y = event.acceleration.y;
	double acc_z = event.acceleration.z;
	return sqrt(acc_x*acc_x + acc_y*acc_y + acc_z*acc_z);
}
