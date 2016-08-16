/* Animated Logo Project
 */

#include "config.h"
#include "math.h"
#include "SdFat.h"
#include "GIFDecoder.h"
#include "SparkFun_APDS9960.h"
#include "gamma.h"
#include "ColorList.h"

#include "GestureSensor.h"
#include "ColorAnimation.h"
#include "DualColorAnimation.h"
#include "BreatheAnimation.h"
#include "BreatheRainbowAnimation.h"
#include "GifAnimation.h"

#include "NeopixelAnimationContext.h"
#include <deque>
using namespace std;

SYSTEM_THREAD(ENABLED);
// Must use a different product ID for Electron vs Photon
#if PLATFORM_ID == 10
PRODUCT_ID(733);
PRODUCT_VERSION(1);
#elif PLATFORM_ID == 6
//PRODUCT_ID(832);
//PRODUCT_VERSION(1);
#endif

void addStartupAnimations();
int startBreatheAnimation(String color);
int startColorAnimation(String color);
int startDualColorAnimation(String color);
int startBreatheRainbowAnimation();
int startGifAnimation(String name);
int displayOff(String);
int publishListOfGif(String);

void processDuringAnimation();
NeopixelAnimationContext context(processDuringAnimation);

/* Queue of animations. The front of the queue is the current animation */
deque<Animation *> animationQueue;

GestureSensor gesture;

SdFat sd;

/** Battery charger **/
PMIC batteryCharger;

/****************************************/


int numFiles, currentFile;


void setupAnimationContext() {
    // Initialize and clear strip
    context.begin();
    context.show();
}

void setupSdCard() {
    // initialize the SD card at full speed
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
        Serial.println("No SD card");
    }
}

void setupCloud() {
    static bool done = false;
    if (!done && Particle.connected()) {
        Particle.function("breathe", startBreatheAnimation);
        Particle.function("color", startColorAnimation);
        Particle.function("gif", startGifAnimation);
        Particle.function("off", displayOff);
        Particle.function("lsGif", publishListOfGif);
        done = true;
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

    // FIXME: disable gesture sensor for now
    //gesture.begin();
    setupAnimationContext();
    setupSdCard();

    addStartupAnimations();
}

void abortCurrentAnimations() {
    for (auto it = animationQueue.begin(), end = animationQueue.end(); it != end; ++it) {
        (*it)->abort();
    }
}

void addAnimation(Animation *anim) {
    animationQueue.push_back(anim);
}

void addDefaultAnimation() {
    Animation *anim = new BreatheAnimation{context, ParticleBlue, Animation::FOREVER};
    addAnimation(anim);
}

void shuffle(int *indices, int numFiles) {
    for(int i = numFiles - 1; i > 0; --i) {
        int temp = indices[i];
        int target = random(i + 1);
        indices[i] = indices[target];
        indices[target] = temp;
    }
}

// Play all GIF then breathe rainbows for a while when the device starts
void addStartupAnimations() {
    int numFiles = enumerateGIFFiles(GIF_DIRECTORY, false);

    // randomize gifs
    int *indices = new int[numFiles];
    for(int i = 0; i < numFiles; i++) {
        indices[i] = i;
    }
    shuffle(indices, numFiles);

    for(int i = 0; i < numFiles; i++) {
        char pathname[60];
        getGIFFilenameByIndex(GIF_DIRECTORY, indices[i], pathname);
        addAnimation(new GifAnimation{context, pathname, STARTUP_ANIMATION_TIME});
    }

    addAnimation(new BreatheRainbowAnimation{context, STARTUP_BREATHE_TIME});
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
        runCurrentAnimation();
        nextAnimation();
    }
}

// logo breathe sepia
// logo breathe rainbow
int startBreatheAnimation(String colorName) {

    colorName.trim();
    if (colorName.equals("rainbow")) {
        return startBreatheRainbowAnimation();
    }

    Color color = colorFromName(colorName);

    Animation *anim = new BreatheAnimation{context, color, CLOUD_ANIMATION_TIME};
    abortCurrentAnimations();
    addAnimation(anim);

    return 0;
}

// logo color purple
int startColorAnimation(String colorName) {
    if (colorName.indexOf(",") != -1) {
        return startDualColorAnimation(colorName);
    }

    colorName.trim();
    Color color = colorFromName(colorName);

    Animation *anim = new ColorAnimation{context, color, CLOUD_ANIMATION_TIME};
    abortCurrentAnimations();
    addAnimation(anim);

    return 0;
}

// logo color purple, green
int startDualColorAnimation(String colorNames) {
    int commaPos = colorNames.indexOf(",");

    String centerColorName = colorNames.substring(0, commaPos);
    String arrowColorName = colorNames.substring(commaPos + 1);

    centerColorName.trim();
    Color centerColor = colorFromName(centerColorName);

    arrowColorName.trim();
    Color arrowColor = colorFromName(arrowColorName);

    Animation *anim = new DualColorAnimation{context, centerColor, arrowColor, CLOUD_ANIMATION_TIME};
    abortCurrentAnimations();
    addAnimation(anim);

    return 0;
}

int startBreatheRainbowAnimation() {
    Animation *anim = new BreatheRainbowAnimation{context, CLOUD_ANIMATION_TIME};

    abortCurrentAnimations();
    addAnimation(anim);

    return 0;
}

int startGifAnimation(String name) {
    name.trim();
    if (name.length() == 0) {
        return -1;
    }

    name.toLowerCase();
    if (!name.endsWith(".gif")) {
        name += ".gif";
    }
    String pathname = String(GIF_DIRECTORY) + name;

    if (!isValidFile(pathname)) {
        return -2;
    }

    Animation *anim = new GifAnimation{context, pathname, CLOUD_ANIMATION_TIME};
    abortCurrentAnimations();
    addAnimation(anim);

    return 0;
}

int displayOff(String) {
    Color black{0, 0, 0};
    Animation *anim = new ColorAnimation{context, black, Animation::FOREVER};
    abortCurrentAnimations();
    addAnimation(anim);

    return 0;
}


int publishListOfGif(String) {
    String list = "[";
    forEachGIFFile(GIF_DIRECTORY, [&list](const char *filename) {
        if (list.length() > 1) {
            list += ",";
        }
        list += "\"";
        list += filename;
        list += "\"";
    });
    list += "]";
    Particle.publish("gifs", list, PRIVATE);

    return 0;
}

void playNextGif() {
    // currentFile will be incremented after the current animation stops
    currentFile = (currentFile - 2 + numFiles) % numFiles;
}

void playPreviousGif() {
}

bool processGestureSensor() {
    switch (gesture.getGesture()) {
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

    return false;
}

void processDuringAnimation() {
    setupCloud();
    processGestureSensor();

    Particle.process();
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

