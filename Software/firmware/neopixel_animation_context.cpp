#include "neopixel_animation_context.h"

#include "PixelMapping.h"
#include "config.h"

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

void NeopixelAnimationContext::drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
    int stripPosition = pixelCoordToLinearOffset(x, y);
    if (stripPosition >= 0) {
        strip.setPixelColor(stripPosition, red, green, blue);
    }
}

void NeopixelAnimationContext::wait(uint32_t ms) {
    uint32_t start = millis();
    do {
        if (process) {
            process();
        }

        delay(1);
    } while(millis() - start > ms);
}

uint32_t NeopixelAnimationContext::now() {
    return millis();
}

