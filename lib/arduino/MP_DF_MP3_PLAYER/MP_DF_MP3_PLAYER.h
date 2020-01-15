#ifndef MP_DF_MP3_PLAYER_H
#define MP_DF_MP3_PLAYER_H

#include "MP_DEVICE.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

class MP_DF_MP3_PLAYER
{
public:
	MP_DF_MP3_PLAYER(uint8_t tx, uint8_t rx);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    void playMP3(int index);
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
    void setEQ(char * EQ);

    int getVolume();
    int getFileCount();
    int getCurrentFileNumber();

private:
    DFRobotDFPlayerMini myDFPlayer;
    SoftwareSerial mySoftwareSerial;

    uint8_t statusType;
    int statusValue;
};

#endif
