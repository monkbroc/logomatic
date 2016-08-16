#include "NeopixelAnimationContext.h"

#include "PixelMapping.h"
#include "config.h"
#include "gamma.h"

NeopixelAnimationContext::NeopixelAnimationContext(ProcessCallback process) 
    : strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE),
    process(process)
{
}

// How many pixels wide and tall is the display
Rect NeopixelAnimationContext::displaySize() {
    return Rect{x: 0, y: 0, width: 17, height: 17 };
}

void NeopixelAnimationContext::begin() {
    strip.begin();
}

void NeopixelAnimationContext::clear() {
    strip.clear();
}

void NeopixelAnimationContext::show() {
    strip.show();
}

void NeopixelAnimationContext::drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
    int stripPosition = pixelCoordToLinearOffset(x, y);
    if (stripPosition >= 0) {
        red = ((uint16_t)colorGamma[red] * brightness) / 256;
        green = ((uint16_t)colorGamma[green] * brightness) / 256;
        blue = ((uint16_t)colorGamma[blue] * brightness) / 256;
        strip.setPixelColor(stripPosition, red, green, blue);
    }
}

void NeopixelAnimationContext::wait(uint32_t ms, bool *abort) {
    uint32_t start = millis();

    // Provide a default for the abort pointer
    bool dontAbort = false;
    if (!abort) {
        abort = &dontAbort;
    }

    do {
        if (process) {
            process();
        }
        HAL_Delay_Milliseconds(1);
    } while(!(*abort) && millis() - start < ms);
}

uint32_t NeopixelAnimationContext::now() {
    return millis();
}

