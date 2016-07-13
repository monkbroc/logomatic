/* Animated Logo Project
 */

#include "neopixel.h" // Hardware-specific library
#include "PixelMapping.h"
#include "GIFDecoder.h"
#include "math.h"
#include "SdFat.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

/* LED strip configuration */
#define PIXEL_PIN A7
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);


/** SD card configuration and CS pins**/
#define SPI_CONFIGURATION 0

SdFat sd;
const uint8_t chipSelect = A2;
/****************************************/

/********** RGB565 Color definitions **********/
#define Black           0x0000
#define Navy            0x000F
#define DarkGreen       0x03E0
#define DarkCyan        0x03EF
#define Maroon          0x7800
#define Purple          0x780F
#define Olive           0x7BE0
#define LightGrey       0xC618
#define DarkGrey        0x7BEF
#define Blue            0x001F
#define Green           0x07E0
#define Cyan            0x07FF
#define Red             0xF800
#define Magenta         0xF81F
#define Yellow          0xFFE0
#define White           0xFFFF
#define Orange          0xFD20
#define GreenYellow     0xAFE5
#define Pink			0xF81F
/**********************************************/


#define DISPLAY_TIME_SECONDS 5

#define GIF_DIRECTORY "/gifs/"

int num_files;

void screenClearCallback(void) {
  strip.clear();
}

void updateScreenCallback(void) {
  strip.show();
}

void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  int stripPosition = pixelCoordToLinearOffset(x, y);
  if(stripPosition >= 0) {
    strip.setPixelColor(stripPosition, red, green, blue);
  }
}

// Setup method runs once, when the sketch starts
void setup() {

	Serial.begin(9600);
    delay(100);
    Serial.println("Logomatic");
    randomSeed(HAL_RNG_GetRandomNumber());

    setScreenClearCallback(screenClearCallback);
    setUpdateScreenCallback(updateScreenCallback);
    setDrawPixelCallback(drawPixelCallback);

    // Initialize and clear strip
    strip.begin();
    strip.show();

    // initialize the SD card at full speed
    if (!sd.begin(chipSelect, SPI_FULL_SPEED)) {
        Serial.println("No SD card");
        while(true);
    }

    // Determine how many GIF files exist
    num_files = enumerateGIFFiles(GIF_DIRECTORY, true);

    if(num_files < 0) {
        Serial.println("No gifs directory");
        while(true);
    }

    if(!num_files) {
        Serial.println("Empty gifs directory");
        while(true);
    }
}


void shuffle(int *indices, int num_files) {
    for(int i = num_files - 1; i > 0; --i) {
        int temp = indices[i];
        int target = random(i + 1);
        indices[i] = indices[target];
        indices[target] = temp;
    }
}

void loop() {
    unsigned long futureTime;
    char pathname[30];

    int *indices = new int[num_files];
    for(int i = 0; i < num_files; i++) {
        indices[i] = i;
    }

    // Do forever
    while (true) {
        shuffle(indices, num_files);

        for(int index = 0; index < num_files; index++) {
            // Can clear screen for new animation here, but this might cause flicker with short animations
            // matrix.fillScreen(Black);
            // matrix.swapBuffers(true);

            getGIFFilenameByIndex(GIF_DIRECTORY, indices[index], pathname);

            // Calculate time in the future to terminate animation
            futureTime = millis() + (DISPLAY_TIME_SECONDS * 1000);

            while (futureTime > millis()) {
                processGIFFile(pathname);
            }
        }
    }
}

