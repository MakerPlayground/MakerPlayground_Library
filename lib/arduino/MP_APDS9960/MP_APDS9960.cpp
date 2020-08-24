#include "MP_APDS9960.h"

MP_APDS9960::MP_APDS9960()
	:apds(SparkFun_APDS9960())
{
}

int MP_APDS9960::init()
{
	this->end_time = 0;

	// Initialize APDS-9960 (configure I2C and initial values)
	if ( !apds.init() ) {
		return MP_ERR_CONNECT_DEVICE;
	}

	// Adjust the Proximity sensor gain
	if ( !apds.setProximityGain(PGAIN_2X) ) {
		return MP_ERR_CONFIG_DEVICE;
	}

	// Start running the APDS-9960 proximity sensor (no interrupts)
	if ( !apds.enableProximitySensor(false) ) {
		return MP_ERR_CONFIG_DEVICE;
	}
	
	//Serial.println(F("APDS-9960 initialization complete"));
	//Serial.println(F("Proximity sensor is now running"));
	return MP_ERR_OK;

//    // Start running the APDS-9960 gesture sensor engine
//    if ( apds.enableGestureSensor(false) ) {
//        Serial.println(F("Gesture sensor is now running"));
//    } else {
//        Serial.println(F("Something went wrong during gesture sensor init!"));
//    }
}

void MP_APDS9960::update(unsigned long current_time)
{
	if (current_time - end_time > 20) {
		if (!apds.readProximity(this->x)) {
			this->isFailOnReading = true;
		} else {
			this->isFailOnReading = false;
		}

		if (this->isFailOnReading) {
			cm = 20;
		} else {
			double distance = 0.000858238872*x*x - 0.233873883*x + 26.3131278;
			if(x > 136 || distance < 10 ) {
				cm = 10;
			}
			else if (distance > 20) {
				cm = 20;
			}
			else {
				cm = distance;
			}
		}
		end_time = current_time;
	}
}

void MP_APDS9960::printStatus()
{
	Serial.print(F("Sensor is now "));
	Serial.println(this->isFailOnReading ? "inactive": "active");
	if( !this->isFailOnReading ) {
		Serial.print(F("distance = "));
		Serial.println(this->getDistance());
	}
}

double MP_APDS9960::getDistance()
{
	return cm;
}

bool MP_APDS9960::isGestureDetected(char c[])
{
	if ( apds.isGestureAvailable() ) {
		int gesture = apds.readGesture();
		return (gesture == DIR_UP && c[0] == 'U') 
		|| (gesture == DIR_DOWN && c[0] == 'D')
		|| (gesture == DIR_LEFT && c[0] == 'L')
		|| (gesture == DIR_RIGHT && c[0] == 'R')
		|| (gesture == DIR_NEAR && c[0] == 'N')
		|| (gesture == DIR_FAR && c[0] == 'F');
	}
	return false;
}

bool MP_APDS9960::isGestureNotDetected()
{
	return (apds.readGesture() == DIR_NONE);
}
