#include "BreatheRainbowAnimation.h"
#include "Color.h"

// Start with Particle blue color
const uint8_t BreatheRainbowAnimation::initialWheelPos = 190;

BreatheRainbowAnimation::BreatheRainbowAnimation(
			AnimationContext &context,
			uint32_t duration)
    : Animation{context, duration},
    breathe(nullptr)
{
}

void BreatheRainbowAnimation::run() {
	uint32_t start = context.now();
    uint8_t c = initialWheelPos;
    Color color;

	while(context.now() - start < duration) {
        if(_abort) return;

        color = Wheel(c);
        // A single cycle breathe animation
        BreatheAnimation anim{context, color, 1};
        breathe = &anim;
        anim.run();
        breathe = nullptr;

        c += 10;
    }
}

void BreatheRainbowAnimation::abort() {
    _abort = true;
    if (breathe) {
        breathe->abort();
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
Color BreatheRainbowAnimation::Wheel(uint8_t WheelPos) {
  if(WheelPos < 85) {
   return Color{red: WheelPos * 3, green: 255 - WheelPos * 3, blue: 0};
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return Color{red: 255 - WheelPos * 3, green: 0, blue: WheelPos * 3};
  } else {
   WheelPos -= 170;
   return Color{red: 0, green: WheelPos * 3, blue: 255 - WheelPos * 3};
  }
}

