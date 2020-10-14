#ifndef MP_M5STACK_FINGERHAT_H
#define MP_M5STACK_FINGERHAT_H

#include "MP_DEVICE.h"
#include "finger.h"

enum DeviceStatus {
  IDLE,
  ADDING,
  VALIDATING,
  DELETING
};

class MP_M5STACK_FINGERHAT
{
public:
	MP_M5STACK_FINGERHAT(uint8_t pin_tx, uint8_t pin_rx);
	int init();
	void update(unsigned long current_time);
	void printStatus();

  void addFingerprint();
  void validateFingerprint();
  void deleteFingerprint(uint16_t index);
  void deleteAllFingerprints();

  bool isAddSuccess();
  bool isAddFail();
  bool isValidateSuccess();
  bool isValidateFail();
  bool isDeleteSuccess();
  bool isDeleteFail();

  int getFinger_Count();

private:
	uint8_t pin_tx, pin_rx;
  FingerPrint FP_M;
  DeviceStatus d_status = IDLE;
  bool addSuccess = false;
  bool addFail = false;
  bool validateSuccess = false;
  bool validateFail = false;
  bool deleteSuccess = false;
  bool deleteFail = false;
  uint16_t userNum = 0;
};

#endif
