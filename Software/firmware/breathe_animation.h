#pragma once

#include "animation.h"

class BreatheAnimation : public Animation {
public:
	BreatheAnimation(
			AnimationContext &context,
			uint8_t red, uint8_t green, uint8_t blue,
			uint32_t duration);

	void run() override;
	void abort() override;

protected:
	void fillScreen(uint8_t brightness);

	static uint8_t delay;

	uint8_t r, g, b;
	bool _abort;
};
