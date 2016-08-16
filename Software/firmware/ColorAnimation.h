#pragma once

#include "Animation.h"
#include "Color.h"

class ColorAnimation : public Animation {
public:
	ColorAnimation(
			AnimationContext &context,
			Color color,
			uint32_t duration);

	void run() override;

protected:
	void fillScreen();

	Color color;
};
