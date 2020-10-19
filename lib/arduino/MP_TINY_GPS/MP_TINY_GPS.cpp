#include "MP_TINY_GPS.h"

MP_TINY_GPS::MP_TINY_GPS(uint8_t gps_tx, uint8_t gps_rx, int baud)
	:ss(gps_tx, gps_rx)
	,GPSBaud(baud)
{
}

int MP_TINY_GPS::init()
{
	isGPSDetected = false;
	ss.begin(GPSBaud);
	return MP_ERR_OK;
}

void MP_TINY_GPS::update(unsigned long current_time) 
{
	// while(ss.available()) {
	// 	if (gps.encode(ss.read()) && gps.location.isValid()) {
	// 		lat = gps.location.lat();
	// 		lon = gps.location.lng();
	// 	}
	// }
	// isGPSDetected = !(gps.charsProcessed() < 10);
	while(ss.available() > 0) {
	    gps.encode(ss.read());
	}
	if (gps.location.isValid() && gps.location.isUpdated()) {
		lat = gps.location.lat();
		lon = gps.location.lng();
		isGPSDetected = true;
	}
	else if (gps.location.age() > 2000) {
		isGPSDetected = false;
	}
}

bool MP_TINY_GPS::isDataValid() {
	return isGPSDetected;
}

bool MP_TINY_GPS::isDataInvalid() {
	return !isGPSDetected;
}

void MP_TINY_GPS::printStatus()
{
	if (isGPSDetected) {
		Serial.print(F("lat, long = "));
		Serial.print(lat, 9);
		Serial.print(F(","));
		Serial.print(lon, 9);
	} else {
		Serial.print(F("No GPS detected"));
	}
}

double MP_TINY_GPS::getLatitude()
{
	return lat;
}

double MP_TINY_GPS::getLongitude()
{
	return lon;
}