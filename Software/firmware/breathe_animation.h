#pragma once

#include "animation.h"
#include "color.h"

class BreatheAnimation : public Animation {
public:
	BreatheAnimation(
			AnimationContext &context,
			Color color,
			uint32_t duration);

	void run() override;
	void abort() override;

protected:
	void fillScreen(uint8_t brightness);

	static uint8_t delay;

	Color color;
	bool _abort;
};
