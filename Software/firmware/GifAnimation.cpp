#include "GifAnimation.h"

#include "GIFDecoder.h"
#include "SdFat.h"
#include "gamma.h"

// For use with C callback methods from Gif library
GifAnimation *GifAnimation::current = nullptr;

bool GifAnimation::setupDone = false;

GifAnimation::GifAnimation(
			AnimationContext &context,
			String filename,
			uint32_t duration)
	: Animation{context, duration},
    filename(filename)
{
    if (!setupDone) {
        setupCallbacks();
    }
}

void GifAnimation::run()
{
    current = this;
    uint32_t start = context.now();

    context.clear();

    while(context.now() - start < duration) {
        if(_abort) return;

        processGIFFile(filename.c_str());
    }
}

void GifAnimation::screenClearCallback() {
    context.clear();
}

void GifAnimation::updateScreenCallback() {
    context.show();
}

void GifAnimation::drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
    context.drawPixel(x, y, red, green, blue);
}

bool GifAnimation::cancellableDelay(uint32_t ms) {
    context.wait(ms, &_abort);
    return _abort;
}

// Callbacks for Gif library
// Delegate to current animation instance
void GifAnimation::setupCallbacks() {
    setScreenClearCallback(screenClearCallbackStatic);
    setUpdateScreenCallback(updateScreenCallbackStatic);
    setDrawPixelCallback(drawPixelCallbackStatic);
    setDelayCallback(cancellableDelayStatic);

    setupDone = true;
}

void GifAnimation::screenClearCallbackStatic() {
    if (current) {
        current->screenClearCallback();
    }
}

void GifAnimation::updateScreenCallbackStatic() {
    if (current) {
        current->updateScreenCallback();
    }
}

void GifAnimation::drawPixelCallbackStatic(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
    if (current) {
        current->drawPixelCallback(x, y, red, green, blue);
    }
}

bool GifAnimation::cancellableDelayStatic(uint32_t ms) {
    if (current) {
        return current->cancellableDelay(ms);
    }
    return false;
}

