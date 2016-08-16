#pragma once

#include "Animation.h"
#include "Color.h"

class BreatheAnimation : public Animation {
public:
	BreatheAnimation(
			AnimationContext &context,
			Color color,
			uint32_t duration);

	void run() override;

protected:
	void fillScreen(uint8_t brightness);

	static uint8_t delay;

	Color color;
};
