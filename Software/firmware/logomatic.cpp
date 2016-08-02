/* Animated Logo Project
 */

#include "config.h"
#include "math.h"
#include "SdFat.h"
#include "GIFDecoder.h"
#include "SparkFun_APDS9960.h"
#include "gamma.h"

#include "color_animation.h"
#include "breathe_animation.h"
#include "breathe_rainbow_animation.h"
#include "gif_animation.h"

#include "neopixel_animation_context.h"
#include <deque>
using namespace std;

SYSTEM_THREAD(ENABLED);

static const Color ParticleBlue(0,173,239);

void processInput();
NeopixelAnimationContext context(processInput);

/* Queue of animations. The front of the queue is the current animation */
deque<Animation *> animationQueue;

/** Gesture sensor configuration **/
#define APDS9960_INT    D2 // Needs to be an interrupt pin
bool gestureDetected = false;

SparkFun_APDS9960 apds = SparkFun_APDS9960();

/** SD card configuration and CS pins**/
#define SPI_CONFIGURATION 0

SdFat sd;
const uint8_t chipSelect = A2;

/** Battery charger **/
PMIC batteryCharger;

/****************************************/


int numFiles, currentFile;

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

void setupAnimationContext() {
    // Initialize and clear strip
    context.begin();
    context.show();
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
    // Stop red LED blinking on Electron
    batteryCharger.disableCharging();

	Serial.begin(9600);
    delay(100);
    Serial.println("Logomatic");
    randomSeed(HAL_RNG_GetRandomNumber());

    setupGestureSensor();
    setupAnimationContext();
    setupSdCard();
}

void abortCurrentAnimation() {
    if (!animationQueue.empty()) {
        animationQueue.front()->abort();
    }
}

void addDefaultAnimation() {
    Animation *anim = new BreatheAnimation{context, ParticleBlue, Animation::FOREVER};
    animationQueue.push_back(anim);
}

void nextAnimation() {
    if (!animationQueue.empty()) {
        Animation *previousAnim = animationQueue.front();
        animationQueue.pop_front();
        delete previousAnim;
    }

    if (animationQueue.empty()) {
        addDefaultAnimation();
    }
}

void runCurrentAnimation() {
    if (!animationQueue.empty()) {
        animationQueue.front()->run();
    }
}

void loop() {
    while (true) {
        nextAnimation();
        runCurrentAnimation();
    }
}

void playNextGif() {
    // currentFile will be incremented after the current animation stops
    currentFile = (currentFile - 2 + numFiles) % numFiles;
}

void playPreviousGif() {
}

bool processGestureSensor() {
    if (apds.isGestureAvailable()) {
        switch (apds.readGesture()) {
            case DIR_LEFT:
                Serial.println("Left gesture!");
                playNextGif();
                return true;
                break;
            case DIR_RIGHT:
                Serial.println("Right gesture!");
                playPreviousGif();
                return true;
                break;
            case DIR_UP:
                Serial.println("Up gesture!");
                break;
            case DIR_DOWN:
                Serial.println("Down gesture!");
                break;
            case DIR_NEAR:
                Serial.println("Near gesture!");
                break;
            case DIR_FAR:
                Serial.println("Far gesture!");
                break;
        }
    }

    return false;
}

void processInput() {
    processGestureSensor();

}

/*

void shuffle(int *indices, int numFiles) {
    for(int i = numFiles - 1; i > 0; --i) {
        int temp = indices[i];
        int target = random(i + 1);
        indices[i] = indices[target];
        indices[target] = temp;
    }
}

void loop() {
    char pathname[30];

    int *indices = new int[numFiles];
    for(int i = 0; i < numFiles; i++) {
        indices[i] = i;
    }

    // Do forever
    while (true) {
        shuffle(indices, numFiles);

        while(currentFile < numFiles) {
            getGIFFilenameByIndex(GIF_DIRECTORY, indices[currentFile], pathname);

            GifAnimation anim(context, pathname, DISPLAY_TIME_SECONDS * 1000);
            anim.run();

            currentFile++;
        }
        currentFile = 0;
    }
}
*/

