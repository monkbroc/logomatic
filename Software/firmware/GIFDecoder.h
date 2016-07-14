#ifndef _GIFDECODER_H_
#define _GIFDECODER_H_

//#include <stdint.h>
#include "Particle.h"

typedef void (*callback)(void);
typedef void (*pixel_callback)(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue);
typedef bool (*delay_callback)(uint32_t ms);

void setScreenClearCallback(callback f);
void setUpdateScreenCallback(callback f);
void setDrawPixelCallback(pixel_callback f);
void setDelayCallback(delay_callback f);


// public
int enumerateGIFFiles(const char *directoryName, boolean displayFilenames);
void getGIFFilenameByIndex(const char *directoryName, int index, char *pnBuffer);
void chooseRandomGIFFilename(const char *directoryName, char *pnBuffer);
int processGIFFile(const char * pathname);

// Error codes
#define ERROR_NONE		           0
#define ERROR_FILEOPEN		       -1
#define ERROR_FILENOTGIF	       -2
#define ERROR_BADGIFFORMAT         -3
#define ERROR_UNKNOWNCONTROLEXT	   -4
#define ERROR_ABORTED              -5

// private
#ifndef SmartMatrix_h
 typedef struct rgb24 {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb24;
#endif

void lzw_decode_init (int csize, byte *buf);
int lzw_decode(byte *buf, int len);
int decompressAndDisplayFrame();

#endif
