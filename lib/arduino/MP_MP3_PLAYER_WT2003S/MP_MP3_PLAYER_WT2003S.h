#ifndef MP_MP3_PLAYER_WT2003S_H
#define MP_MP3_PLAYER_WT2003S_H

#include "MP_DEVICE.h"
#include "SoftwareSerial.h"
#include "WT2003S_Player.h"

class MP_MP3_PLAYER_WT2003S
{
public:
	MP_MP3_PLAYER_WT2003S(uint8_t tx, uint8_t rx);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    void playMP3ByIndex(int index);
    void playMP3ByName(char* name);
    void playNextMP3();
    void playPrevMP3();
    void pause();
    void startFromPause();
    void enableLoop();
    void enableLoopAll();
    void disableLoop();
    void disableLoopAll();
    void setVolume(int volume);
    void volumeUp();
    void volumeDown();
//    void setEQ(uint8_t EQ);

    int getVolume();
    int getFileCount();
    int getCurrentFileNumber();

private:
    SoftwareSerial mySoftwareSerial;
    WT2003S<SoftwareSerial> player;

    uint8_t statusType;
    int statusValue;
};

#endif
