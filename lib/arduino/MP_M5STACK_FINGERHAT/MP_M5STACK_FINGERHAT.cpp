#include "MP_M5STACK_FINGERHAT.h"

MP_M5STACK_FINGERHAT::MP_M5STACK_FINGERHAT(uint8_t pin_tx, uint8_t pin_rx)
	: pin_tx(pin_tx)
  , pin_rx(pin_rx)
{
}

int MP_M5STACK_FINGERHAT::init()
{
  Serial2.begin(19200, SERIAL_8N1, pin_rx, pin_tx);
  userNum = FP_M.fpm_getUserNum();
  if (userNum == 255) {
    return MP_ERR_CONNECT_DEVICE;
  }
	return MP_ERR_OK;
}

void MP_M5STACK_FINGERHAT::update(unsigned long current_time)
{
}

void MP_M5STACK_FINGERHAT::printStatus()
{
}

void MP_M5STACK_FINGERHAT::addFingerprint()
{
  d_status = ADDING;
  uint8_t res1 = FP_M.fpm_addUser(userNum, 1);
  if(res1 == ACK_SUCCESS) { // Add success
    addSuccess = true;
    userNum = FP_M.fpm_getUserNum();
  } else if(res1 == ACK_FAIL) { // Communication fail
    addFail = true;
  } else if(res1 == ACK_FULL) { // User full
    addFail = true;
  } else { // Timeout
    addFail = true;
  }
  d_status = IDLE;
}

void MP_M5STACK_FINGERHAT::validateFingerprint()
{
  d_status = VALIDATING;
  uint8_t res1 = FP_M.fpm_compareFinger();
  if(res1 == ACK_SUCCESS){
    validateSuccess = true;
  }
  else if(res1 == ACK_NOUSER){
    validateFail = true;
  }
  else if(res1 == ACK_TIMEOUT){
    validateFail = true;
  }
  else {
    validateFail = true;
  }
  d_status = IDLE;
}

void MP_M5STACK_FINGERHAT::deleteFingerprint(uint16_t index)
{
  d_status = DELETING;
  uint8_t res1 = FP_M.fpm_deleteUser(index);
  if(res1 == ACK_SUCCESS) {
    deleteSuccess = true;
    userNum = FP_M.fpm_getUserNum();
  } else {
    deleteFail = true;
  }
  d_status = IDLE;
}

void MP_M5STACK_FINGERHAT::deleteAllFingerprints()
{
  d_status = DELETING;
  uint8_t res1 = FP_M.fpm_deleteAllUser();
    if(res1 == ACK_SUCCESS) {
    deleteSuccess = true;
    userNum = FP_M.fpm_getUserNum();
  } else {
    deleteFail = true;
  }
  d_status = IDLE;
}

bool MP_M5STACK_FINGERHAT::isAddSuccess()
{
  if (addSuccess) {
    addSuccess = false;
    return true;
  }
  return false;
}

bool MP_M5STACK_FINGERHAT::isAddFail()
{
  if (addFail) {
    addFail = false;
    return true;
  }
  return false;
}

bool MP_M5STACK_FINGERHAT::isValidateSuccess()
{
  if (validateSuccess) {
    validateSuccess = false;
    return true;
  }
  return false;
}

bool MP_M5STACK_FINGERHAT::isValidateFail()
{
  if (validateFail) {
    validateFail = false;
    return true;
  }
  return false;
}

bool MP_M5STACK_FINGERHAT::isDeleteSuccess()
{
  if (deleteSuccess) {
    deleteSuccess = false;
    return true;
  }
  return false;
}

bool MP_M5STACK_FINGERHAT::isDeleteFail()
{
  if (deleteFail) {
    deleteFail = false;
    return true;
  }
  return false;
}

int MP_M5STACK_FINGERHAT::getFinger_Count()
{
  return userNum;
}