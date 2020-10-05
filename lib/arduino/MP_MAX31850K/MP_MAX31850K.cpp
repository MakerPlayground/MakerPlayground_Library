#include "MP_MAX31850K.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define REFRESH_INTERVAL 100
#define TEMP_RESOLUTION 9


MP_MAX31850K::MP_MAX31850K(uint8_t pin)
  : wire(OneWire(pin))
  , sensors(DallasTemperature(&wire))
{

}

int MP_MAX31850K::init() 
{
  sensors.begin();
  int numberOfDevices = sensors.getDeviceCount();
  if (numberOfDevices < 1) {
    return MP_ERR_CONNECT_DEVICE;
  }

  /* We support only one device. */
  if(!sensors.getAddress(tempDeviceAddress, 0)) {
    return MP_ERR_CONFIG_DEVICE;
  }

  return MP_ERR_OK;
}

void MP_MAX31850K::update(unsigned long current_time) {
  if (current_time - lastMillis >= REFRESH_INTERVAL) {
    sensors.requestTemperatures();
    temperature = sensors.getTempC(tempDeviceAddress);
    lastMillis = current_time;
  }
}

void MP_MAX31850K::printStatus() {
  Serial.print(F("Temperature = "));
  Serial.print(temperature);
  Serial.print(F(" celcius"));
}

double MP_MAX31850K::getTemperature() {
  return temperature;
}