/* The info to perform an animation using a Neopixel strip
 */
#pragma once

#include "animation_context.h"
#include <functional>

#include "neopixel.h" // Hardware-specific library

typedef std::function<void(void)> ProcessCallback;

class NeopixelAnimationContext : public AnimationContext {
public:
    NeopixelAnimationContext(ProcessCallback process);

    void begin();

	virtual Rect displaySize() override;
	virtual void clear() override;
	virtual void show() override;
	virtual void drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) override;
	virtual void wait(uint32_t ms) override;
	virtual uint32_t now() override;

protected:
   Adafruit_NeoPixel strip; 
   ProcessCallback process;
};

