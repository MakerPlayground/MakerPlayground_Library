#include "MP_MP3_PLAYER_WT2003S.h"

MP_MP3_PLAYER_WT2003S::MP_MP3_PLAYER_WT2003S(uint8_t tx, uint8_t rx)
    : mySoftwareSerial(tx, rx)
{
}

int MP_MP3_PLAYER_WT2003S::init()
{
    mySoftwareSerial.begin(9600);
    player.init(mySoftwareSerial);
    player.volume(16);
    return MP_ERR_OK;
}

void MP_MP3_PLAYER_WT2003S::update(unsigned long current_time)
{
}

void MP_MP3_PLAYER_WT2003S::printStatus()
{
}

void MP_MP3_PLAYER_WT2003S::playMP3ByIndex(int index)
{
    player.playSDRootSong(index);
}

void MP_MP3_PLAYER_WT2003S::playMP3ByName(char* name)
{
    player.playSDSong(name);
}

void MP_MP3_PLAYER_WT2003S::playNextMP3()
{
    player.next();
}

void MP_MP3_PLAYER_WT2003S::playPrevMP3()
{
    player.previous();
}

void MP_MP3_PLAYER_WT2003S::pause()
{
    player.pause_or_play();
}

void MP_MP3_PLAYER_WT2003S::startFromPause()
{
    player.pause_or_play();
}

void MP_MP3_PLAYER_WT2003S::enableLoop()
{
    player.playMode(SINGLE_CYCLE);
}

void MP_MP3_PLAYER_WT2003S::enableLoopAll()
{
    player.playMode(CYCLE);
}

void MP_MP3_PLAYER_WT2003S::disableLoop()
{
    player.playMode(SINGLE_SHOT);
}

void MP_MP3_PLAYER_WT2003S::disableLoopAll()
{
    player.playMode(SINGLE_SHOT);
}

void MP_MP3_PLAYER_WT2003S::setVolume(int volume)
{
    player.volume(map(volume, 0, 100, 0, WT2003S_MAX_VOLUME));
}

void MP_MP3_PLAYER_WT2003S::volumeUp()
{
    // Seeed_Serial_MP3_Player library swapped the implementation of volumeUp / volumeDown !!!
    player.volumeDown();
}

void MP_MP3_PLAYER_WT2003S::volumeDown()
{
    // Seeed_Serial_MP3_Player library swapped the implementation of volumeUp / volumeDown !!!
    player.volumeUp();
}

int MP_MP3_PLAYER_WT2003S::getVolume()
{
    return map(player.getVolume(), 0, WT2003S_MAX_VOLUME, 0, 100);
}

int MP_MP3_PLAYER_WT2003S::getFileCount()
{
    return player.getSDMp3FileNumber();
}

int MP_MP3_PLAYER_WT2003S::getCurrentFileNumber()
{
    return player.getTracks();
}