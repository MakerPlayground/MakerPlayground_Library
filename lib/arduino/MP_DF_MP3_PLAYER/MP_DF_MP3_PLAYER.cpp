#include "MP_DF_MP3_PLAYER.h"

MP_DF_MP3_PLAYER::MP_DF_MP3_PLAYER(uint8_t tx, uint8_t rx)
    :mySoftwareSerial(SoftwareSerial(rx, tx))
{
}

int MP_DF_MP3_PLAYER::init()
{
    mySoftwareSerial.begin(9600);
    if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
        return MP_ERR_CONNECTION_OR_SDCARD;
    }
    myDFPlayer.volume(30);
    return MP_ERR_OK;
}

void MP_DF_MP3_PLAYER::update(unsigned long current_time)
{
    if (myDFPlayer.available()) {
        statusType = myDFPlayer.readType();
        statusValue = myDFPlayer.read();
    }
}

void MP_DF_MP3_PLAYER::printStatus()
{
    switch (statusType) {
        case TimeOut:
            Serial.println(F("Time Out!"));
            break;
        case WrongStack:
            Serial.println(F("Stack Wrong!"));
            break;
        case DFPlayerCardInserted:
            Serial.println(F("Card Inserted!"));
            break;
        case DFPlayerCardRemoved:
            Serial.println(F("Card Removed!"));
            break;
        case DFPlayerCardOnline:
            Serial.println(F("Card Online!"));
            break;
        case DFPlayerPlayFinished:
            Serial.print(F("Number:"));
            Serial.print(statusValue);
            Serial.println(F(" Play Finished!"));
            break;
        case DFPlayerError:
            Serial.print(F("DFPlayerError:"));
            switch (statusValue) {
                case Busy:
                    Serial.println(F("Card not found"));
                    break;
                case Sleeping:
                    Serial.println(F("Sleeping"));
                    break;
                case SerialWrongStack:
                    Serial.println(F("Get Wrong Stack"));
                    break;
                case CheckSumNotMatch:
                    Serial.println(F("Check Sum Not Match"));
                    break;
                case FileIndexOut:
                    Serial.println(F("File Index Out of Bound"));
                    break;
                case FileMismatch:
                    Serial.println(F("Cannot Find File"));
                    break;
                case Advertise:
                    Serial.println(F("In Advertise"));
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void MP_DF_MP3_PLAYER::playMP3ByIndex(int index)
{
    myDFPlayer.play(index);
}

void MP_DF_MP3_PLAYER::playNextMP3()
{
    myDFPlayer.next();
}

void MP_DF_MP3_PLAYER::playPrevMP3()
{
    myDFPlayer.previous();
}

void MP_DF_MP3_PLAYER::pause()
{
    myDFPlayer.pause();
}

void MP_DF_MP3_PLAYER::startFromPause()
{
    myDFPlayer.start();
}

void MP_DF_MP3_PLAYER::enableLoop()
{
    myDFPlayer.enableLoop();
}

void MP_DF_MP3_PLAYER::enableLoopAll()
{
    myDFPlayer.enableLoopAll();
}

void MP_DF_MP3_PLAYER::disableLoop()
{
    myDFPlayer.disableLoop();
}

void MP_DF_MP3_PLAYER::disableLoopAll()
{
    myDFPlayer.disableLoopAll();
}

void MP_DF_MP3_PLAYER::setVolume(int volume)
{
    myDFPlayer.volume(map(volume, 0, 100, 0, 30));
}

void MP_DF_MP3_PLAYER::volumeUp()
{
    myDFPlayer.volumeUp();
}

void MP_DF_MP3_PLAYER::volumeDown()
{
    myDFPlayer.volumeDown();
}

void MP_DF_MP3_PLAYER::setEQ(uint8_t EQ)
{
    if (EQ < 0 || EQ > 5) { 
        return; 
    }
    uint8_t EQ_list[] = {
        DFPLAYER_EQ_NORMAL,
        DFPLAYER_EQ_POP,
        DFPLAYER_EQ_ROCK,
        DFPLAYER_EQ_JAZZ,
        DFPLAYER_EQ_CLASSIC,
        DFPLAYER_EQ_BASS
    };
    myDFPlayer.EQ(EQ_list[EQ]);
}

int MP_DF_MP3_PLAYER::getVolume()
{
    return map(myDFPlayer.readVolume(), 0, 30, 0, 100);
}

int MP_DF_MP3_PLAYER::getFileCount()
{
    return myDFPlayer.readFileCounts();
}

int MP_DF_MP3_PLAYER::getCurrentFileNumber()
{
    return myDFPlayer.readCurrentFileNumber();
}