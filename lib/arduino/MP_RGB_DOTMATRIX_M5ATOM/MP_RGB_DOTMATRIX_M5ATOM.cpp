#include "MP_RGB_DOTMATRIX_M5ATOM.h"
extern "C" {
#include "crypto/base64.h"
}

MP_RGB_DOTMATRIX_M5ATOM::MP_RGB_DOTMATRIX_M5ATOM(uint8_t pin)
    : data(NULL)
{
}

int MP_RGB_DOTMATRIX_M5ATOM::init()
{
    M5.begin(false, true, true);
    delay(50);
	return MP_ERR_OK;
}

void MP_RGB_DOTMATRIX_M5ATOM::update(unsigned long current_time) 
{
}

void MP_RGB_DOTMATRIX_M5ATOM::printStatus()
{
}

void MP_RGB_DOTMATRIX_M5ATOM::showBitmap(const char* data)
{
    size_t outputLength;
    unsigned char* decoded = base64_decode((const unsigned char *) data, strlen(data), &outputLength);
    // skip byte 3 by shift the first two byte right and move the head pointer (we insert byte 3 so that the header use
    // all first four character when decode as base64)
    decoded[2] = decoded[1];
    decoded[1] = decoded[0];
    M5.dis.displaybuff(decoded + 1, 0, 0);
    free(decoded);
}

void MP_RGB_DOTMATRIX_M5ATOM::showText(const char* text, uint8_t text_size, int rotation, double red, double green, double blue)
{
    // we must clear the display before free or edit the old buffer so that the display task won't use the buffer while we edit it
    // (we can't acquire the internal semaphore inside of the dot matrix library so the display task may use the buffer while we
    // edit and cause trouble)
    clear();
    if (data != NULL)
    {
        free(data);
    }

    uint8_t textLength = strlen(text);

    data = (unsigned char*) calloc(2 + 6 * 5 * 3 * textLength, sizeof(unsigned char));
    data[0] = textLength * 6;
    data[1] = 5;
    for (uint8_t i=0; i<textLength; i++)
    {
        for (uint8_t j=0; j<5; j++)
        {
            unsigned char* ptr = &data[(i * 6 * 3) + (j * 6 * 3 * textLength) + 2];
            unsigned char buff = font[text[i] - 'A'][j] << 3;
            for (uint8_t k=0; k<5; k++) {
                if ((buff & 0x80) != 0) {
                    *ptr = red;
                    ptr++;
                    *ptr = green;
                    ptr++;
                    *ptr = blue;
                    ptr++;
                } else {
                    *ptr = 0x00;
                    ptr++;
                    *ptr = 0x00;
                    ptr++;
                    *ptr = 0x00;
                    ptr++;
                }
                buff = buff << 1;
            }
        }
    }
    M5.dis.animation(data, 200, M5.dis.kMoveLeft);
}

void MP_RGB_DOTMATRIX_M5ATOM::clear()
{
    M5.dis.clear();
}