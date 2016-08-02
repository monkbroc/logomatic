/* The info to perform an animation using a Neopixel strip
 */
#pragma once

#include "animation_context.h"

#include "neopixel.h" // Hardware-specific library

class NeopixelAnimationContext : public AnimationContext {
public:
    NeopixelAnimationContext();

    void begin();

	virtual Rect displaySize() override;
	virtual void clear() override;
	virtual void show() override;
	virtual void drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) override;
	virtual void wait(uint32_t millis) override;
	virtual uint32_t now() override;

protected:
   Adafruit_NeoPixel strip; 
};

