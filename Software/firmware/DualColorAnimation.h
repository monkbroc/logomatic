#pragma once

#include "Animation.h"
#include "Color.h"

class DualColorAnimation : public Animation {
public:
	DualColorAnimation(
			AnimationContext &context,
			Color centerColor,
			Color arrowColor,
			uint32_t duration);

	void run() override;

protected:
	void fillScreen();

	Color centerColor;
	Color arrowColor;
};
