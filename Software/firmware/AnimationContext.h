/* Info needed to perform an animation
 * How to draw pixels, clear the screen and wait during an animation 
 */
#pragma once

#include "Rect.h"

class AnimationContext {
public:
    virtual ~AnimationContext() {}

	virtual Rect displaySize() = 0;
	virtual void clear() = 0;
	virtual void show() = 0;
	virtual void drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness = 255) = 0;
	virtual void wait(uint32_t millis, bool *abort = nullptr) = 0;
	virtual uint32_t now() = 0;
};

