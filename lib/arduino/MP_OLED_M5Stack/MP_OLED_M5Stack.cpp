#include "MP_OLED_M5Stack.h"

#define SCREEN_WIDTH 320 // OLED display width, in pixels
#define SCREEN_HEIGHT 240 // OLED display height, in pixels
#define UPDATE_INTERVAL 500

MP_OLED_M5Stack::MP_OLED_M5Stack()
{
}

int MP_OLED_M5Stack::init()
{
    display.begin();
    display.setFreeFont(&FreeSans9pt7b);
    clearScreen();
    return ERR_OK;
}

void MP_OLED_M5Stack::update(unsigned long current_time)
{
    if (current_time - last_update > UPDATE_INTERVAL && isDirty) {
        display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
        int currentY = 0;
        for (int i=0; i < MAX_ENTRY_COUNT; i++) {
            currentY += (entries[i].size * 14);
            if (entries[i].message[0]) {
                display.setTextColor(entries[i].color);
                display.setTextSize(entries[i].size);
                display.setCursor(0, currentY);
                display.print(entries[i].message);
            }
        }
        for (int i=0; i < entryWithPositionCount; i++) {
            if (entriesWithPosition[i].message[0]) {
                display.setTextColor(entriesWithPosition[i].color);
                display.setTextSize(entriesWithPosition[i].size);
                display.setCursor(entriesWithPosition[i].x, entriesWithPosition[i].y);
                display.print(entriesWithPosition[i].message);
            }
        }
        display.display();
        last_update = current_time;
    }
}

void MP_OLED_M5Stack::printStatus()
{
}

uint8_t MP_OLED_M5Stack::getSizeFromSizeName(char* size)
{
    if (strcmp(size, "Small") == 0) {
        return 1;
    } else if(strcmp(size, "Medium") == 0) {
        return 2;
    } else if(strcmp(size, "Large") == 0) {
        return 3;
    }
    return 1;
}

uint16_t MP_OLED_M5Stack::getColorFromColorName(char* color)
{
    if (strcmp(color, "Navy") == 0) {
        return TFT_NAVY;
    } else if (strcmp(color, "Dark Green") == 0) {
        return TFT_DARKGREEN;
    } else if (strcmp(color, "Dark Cyan") == 0) {
        return TFT_DARKCYAN;
    } else if (strcmp(color, "Maroon") == 0) {
        return TFT_MAROON;
    } else if (strcmp(color, "Purple") == 0) {
        return TFT_PURPLE;
    } else if (strcmp(color, "Olive") == 0) {
        return TFT_OLIVE;
    } else if (strcmp(color, "Light Grey") == 0) {
        return TFT_LIGHTGREY;
    } else if (strcmp(color, "Dark Grey") == 0) {
        return TFT_DARKGREY;
    } else if (strcmp(color, "Blue") == 0) {
        return TFT_BLUE;
    } else if (strcmp(color, "Green") == 0) {
        return TFT_GREEN;
    } else if (strcmp(color, "Cyan") == 0) {
        return TFT_CYAN;
    } else if (strcmp(color, "Red") == 0) {
        return TFT_RED;
    } else if (strcmp(color, "Magenta") == 0) {
        return TFT_MAGENTA;
    } else if (strcmp(color, "Yellow") == 0) {
        return TFT_YELLOW;
    } else if (strcmp(color, "White") == 0) {
        return TFT_WHITE;
    } else if (strcmp(color, "Orange") == 0) {
        return TFT_ORANGE;
    } else if (strcmp(color, "Green Yellow") == 0) {
        return TFT_GREENYELLOW;
    } else if (strcmp(color, "Pink") == 0) {
        return TFT_PINK;
    }
    return TFT_WHITE;
}

void MP_OLED_M5Stack::showTextAtLine(int line, char* text, char* size, char* color)
{
    int lineIndex = line - 1;
    if (lineIndex >= 0 && lineIndex < MAX_ENTRY_COUNT) {
        strcpy(entries[lineIndex].message, text);
        entries[lineIndex].size = getSizeFromSizeName(size);
        entries[lineIndex].color = getColorFromColorName(color);
        isDirty = true;
    }
}

void MP_OLED_M5Stack::showNumberAtLine(int line, char* label, double value, double decimalPlaces, char* size, char* color)
{
    char* p;
    char buff[33] = "";
    char buff2[33] = "";
    char buff3[33] = "";
    strcpy(buff, label);
    if ((p = strstr(buff, "/value/")) != NULL) {
        strcpy(buff3, p+7);
        dtostrf(value, (decimalPlaces + 2), decimalPlaces, buff2);
        strcpy(p, buff2);
        strcpy(p + strlen(buff2), buff3);
    }
    showTextAtLine(line, buff, size, color);
}

void MP_OLED_M5Stack::showTextAtPosition(int x, int y, char* text, char* size, char* color)
{
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        int storingIndex = -1;
        for(int i=0; i<entryWithPositionCount; i++) {
            if (entriesWithPosition[i].x == x && entriesWithPosition[i].y == y) {
                storingIndex = i;
                break;
            }
        }
        if (entryWithPositionCount == MAX_ENTRY_COUNT) {
            return;
        }
        if (storingIndex == -1) {
            storingIndex = entryWithPositionCount;
            entryWithPositionCount++;
        }
        strcpy(entriesWithPosition[storingIndex].message, text);
        entriesWithPosition[storingIndex].x = x;
        entriesWithPosition[storingIndex].y = y;
        entriesWithPosition[storingIndex].size = getSizeFromSizeName(size);
        entriesWithPosition[storingIndex].color = getColorFromColorName(color);
        isDirty = true;
    }
}

void MP_OLED_M5Stack::showNumberAtPosition(int x, int y, char* label, double value, double decimalPlaces, char* size, char* color)
{
    char* p;
    char buff[33] = "";
    char buff2[33] = "";
    char buff3[33] = "";
    strcpy(buff, label);
    if ((p = strstr(buff, "/value/")) != NULL) {
        strcpy(buff3, p+7);
        dtostrf(value, (decimalPlaces + 2), decimalPlaces, buff2);
        strcpy(p, buff2);
        strcpy(p + strlen(buff2), buff3);
    }
    showTextAtPosition(x, y, buff, size, color);
}

void MP_OLED_M5Stack::clearLine(int line)
{
    strcpy(entries[line-1].message, "");
}

void MP_OLED_M5Stack::clearScreen()
{
    for (int i=0; i<MAX_ENTRY_COUNT; i++) {
        strcpy(entries[i].message, "");
        entries[i].size = getSizeFromSizeName("Small");
    }
    for (int i=0; i<entryWithPositionCount; i++) {
        strcpy(entriesWithPosition[i].message, "");
        entriesWithPosition[i].size = getSizeFromSizeName("Small");
        entriesWithPosition[i].x = -1;
        entriesWithPosition[i].y = -1;
    }
    entryWithPositionCount = 0;
    display.fillScreen(TFT_BLACK);
}