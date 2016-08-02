/* Breathe different colors of the rainbow in a sequence
 */

#pragma once
#include "breathe_animation.h"

class BreatheRainbowAnimation : public Animation {
public:
	BreatheRainbowAnimation(
			AnimationContext &context,
			uint32_t duration);

    void run() override;
    void abort() override;

protected:
    static const uint8_t initialWheelPos;

    Color Wheel(uint8_t WheelPos);

    BreatheAnimation *breathe;
	bool _abort;
};

