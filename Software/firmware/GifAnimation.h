#pragma once

#include "Animation.h"
#include "spark_wiring_string.h"

class GifAnimation : public Animation {
public:
	GifAnimation(
			AnimationContext &context,
            String filename,
			uint32_t duration);

    // Call to set up the callbacks for the Gif library
	void run() override;

protected:
    void screenClearCallback();
    void updateScreenCallback();
    void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue);
    bool cancellableDelay(uint32_t ms);

    static void setupCallbacks();
    static void screenClearCallbackStatic();
    static void updateScreenCallbackStatic();
    static void drawPixelCallbackStatic(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue);
    static bool cancellableDelayStatic(uint32_t ms);

    static GifAnimation *current;
    static bool setupDone;

	String filename;
};
