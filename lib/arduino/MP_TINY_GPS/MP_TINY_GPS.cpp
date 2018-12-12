#include "MP_TINY_GPS.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_TINY_GPS::ERRORS = errors_p;

MP_TINY_GPS::MP_TINY_GPS(uint8_t tx, uint8_t rx, int baud)
	:ss(SoftwareSerial(rx, tx))
	,GPSBaud(baud)
{
}

int MP_TINY_GPS::init()
{
	isGPSDetected = false;
	ss.begin(GPSBaud);
	return 0;
}

void MP_TINY_GPS::update(unsigned long current_time) 
{
	while(ss.available()) {
		if (gps.encode(ss.read()) && gps.location.isValid()) {
			lat = gps.location.lat();
			lon = gps.location.lng();
		}
	}
	isGPSDetected = !(gps.charsProcessed() < 10);
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