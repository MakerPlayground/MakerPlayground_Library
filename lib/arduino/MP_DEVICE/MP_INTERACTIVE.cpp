#include "MP_INTERACTIVE.h"

bool MP_INTERACTIVE::isFreezeSensor() {
    return freezeSensor;
}

void MP_INTERACTIVE::setFreezeSensor(bool isFreeze) {
    freezeSensor = isFreeze;
}

MP_INTERACTIVE MPInteractive;