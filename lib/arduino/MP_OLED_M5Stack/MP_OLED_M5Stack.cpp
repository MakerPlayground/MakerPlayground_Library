#include "MP_OLED_M5Stack.h"

#define SCREEN_WIDTH 320 // OLED display width, in pixels
#define SCREEN_HEIGHT 240 // OLED display height, in pixels

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_OLED_M5Stack::ERRORS = errors_p;

MP_OLED_M5Stack::MP_OLED_M5Stack()
{
}

int MP_OLED_M5Stack::init()
{
    display.begin();
    clearScreen();
    return 0;
}

void MP_OLED_M5Stack::update(unsigned long current_time)
{
}

void MP_OLED_M5Stack::printStatus()
{
}

void MP_OLED_M5Stack::showText(int line, char* text)
{
    display.setTextSize(1);
    display.setTextColor(TFT_WHITE);
    display.setCursor(0, (line - 1) * 8);
    display.fillRect(0, (line - 1) * 8, SCREEN_WIDTH, 8, TFT_BLACK);
    display.print(text);
    display.display();
}

void MP_OLED_M5Stack::showNumber(int line, char* label, double value)
{
    display.setTextSize(1);
    display.setTextColor(TFT_WHITE);
    display.setCursor(0, (line - 1) * 8);
    display.fillRect(0, (line - 1) * 8, SCREEN_WIDTH, 8, TFT_BLACK);

    String tmp(label);
    tmp.replace("/value/", String(value));

    display.print(tmp);
    display.display();
}

void MP_OLED_M5Stack::clearScreen()
{
    display.fillScreen(TFT_BLACK);
}