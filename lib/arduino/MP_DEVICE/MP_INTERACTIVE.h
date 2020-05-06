#ifndef MP_INTERACTIVE_H
#define MP_INTERACTIVE_H

class MP_INTERACTIVE {
public:
    bool isFreezeSensor();
    void setFreezeSensor(bool isFreeze);
private:
    bool freezeSensor;
};

extern MP_INTERACTIVE MPInteractive;

#endif //MP_INTERACTIVE_H