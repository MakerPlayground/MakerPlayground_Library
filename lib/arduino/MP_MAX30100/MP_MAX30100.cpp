#include "MP_MAX30100.h"

#define REFRESH_INTERVAL 10
#define REPORTING_PERIOD_MS     1000

MP_MAX30100::MP_MAX30100() {

}

int MP_MAX30100::init() {
  if (!pox.begin()) {
    return MP_ERR_CONNECT_DEVICE;
  }
  // pox.setOnBeatDetectedCallback(onBeatDetected);
  return MP_ERR_OK;
}

void MP_MAX30100::update(unsigned long current_time) {
  pox.update();
  if (millis() - lastMillis > REFRESH_INTERVAL) {
    hr = pox.getHeartRate();
    spo2 = pox.getSpO2();
    lastMillis = millis();
  }
}

void MP_MAX30100::printStatus() {

}

float MP_MAX30100::getHeart_Rate() {
  return hr;
}

uint8_t MP_MAX30100::getSpO2() {
  return spo2;
}