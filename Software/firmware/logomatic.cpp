/* Animated Logo Project
 */

#include "neopixel.h" // Hardware-specific library
#include "PixelMapping.h"
#include "GIFDecoder.h"
#include "math.h"
#include "SdFat.h"
#include "SparkFun_APDS9960.h"
#include "gamma.h"
#include "color_animation.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

#define DISPLAY_TIME_SECONDS 20

#define GIF_DIRECTORY "/logo/"

/** LED strip configuration **/
#define PIXEL_PIN A7
#define PIXEL_COUNT 113
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

/** Gesture sensor configuration **/
#define APDS9960_INT    D2 // Needs to be an interrupt pin
bool gestureDetected = false;

SparkFun_APDS9960 apds = SparkFun_APDS9960();


/** SD card configuration and CS pins**/
#define SPI_CONFIGURATION 0

SdFat sd;
const uint8_t chipSelect = A2;
/****************************************/


int numFiles, currentFile;

void screenClearCallback(void) {
  strip.clear();
}

void updateScreenCallback(void) {
  strip.show();
}

void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  int stripPosition = pixelCoordToLinearOffset(x, y);
  if (stripPosition >= 0) {
    //strip.setPixelColor(stripPosition, CORRECT_GAMMA(red, green, blue));
    strip.setPixelColor(stripPosition, red, green, blue);
  }
}

bool cancellableDelay(uint32_t ms) {
  // TODO: make this function check the gesture sensor and return true
  // to abort the current GIF display
  delay(ms);
  return false;
}

void gestureInterrupt() {
  gestureDetected = true;
}

void setupGestureSensor() {
  pinMode(APDS9960_INT, INPUT);
  // Initialize interrupt service routine
  attachInterrupt(APDS9960_INT, gestureInterrupt, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if (!apds.init()) {
    Serial.println("Something went wrong during APDS-9960 init!");
    while(true);
  }

  // Start running the APDS-9960 gesture sensor engine
  if (!apds.enableGestureSensor(true)) {
    Serial.println("Something went wrong during gesture sensor init!");
    while(true);
  }

  Serial.println("Gesture sensor is now running");
}

void setupGifDecoder() {
    setScreenClearCallback(screenClearCallback);
    setUpdateScreenCallback(updateScreenCallback);
    setDrawPixelCallback(drawPixelCallback);
    setDelayCallback(cancellableDelay);

    // Initialize and clear strip
    strip.begin();
    strip.show();
}

void setupSdCard() {
    // initialize the SD card at full speed
    if (!sd.begin(chipSelect, SPI_FULL_SPEED)) {
        Serial.println("No SD card");
        while(true);
    }

    // Determine how many GIF files exist
    numFiles = enumerateGIFFiles(GIF_DIRECTORY, true);

    if(numFiles < 0) {
        Serial.println("No gifs directory");
        while(true);
    }

    if(!numFiles) {
        Serial.println("Empty gifs directory");
        while(true);
    }
}

// Setup method runs once, when the sketch starts
void setup() {
	Serial.begin(9600);
    delay(100);
    Serial.println("Logomatic");
    randomSeed(HAL_RNG_GetRandomNumber());


    setupGestureSensor();
    setupGifDecoder();
    setupSdCard();
}

bool handleGesture() {
    if (apds.isGestureAvailable()) {
        switch (apds.readGesture()) {
            case DIR_LEFT:
                // currentFile will be incremented after the current animation stops
                currentFile = (currentFile - 2 + numFiles) % numFiles;
                return true;
                break;
            case DIR_RIGHT:
                return true;
                break;
        }
    }

    return false;
}

void shuffle(int *indices, int numFiles) {
    for(int i = numFiles - 1; i > 0; --i) {
        int temp = indices[i];
        int target = random(i + 1);
        indices[i] = indices[target];
        indices[target] = temp;
    }
}

void loop() {
    unsigned long futureTime;
    char pathname[30];

    int *indices = new int[numFiles];
    for(int i = 0; i < numFiles; i++) {
        indices[i] = i;
    }

    // Do forever
    while (true) {
        shuffle(indices, numFiles);

        while(currentFile < numFiles) {
            // Clear strip for new animation
            strip.clear();

            getGIFFilenameByIndex(GIF_DIRECTORY, indices[currentFile], pathname);

            // Calculate time in the future to terminate animation
            futureTime = millis() + (DISPLAY_TIME_SECONDS * 1000);

            while (futureTime > millis()) {
                int result = processGIFFile(pathname);
                if (result == ERROR_ABORTED) {
                    break;
                }
            }
            currentFile++;
        }
        currentFile = 0;
    }
}

