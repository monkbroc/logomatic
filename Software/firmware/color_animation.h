#include "animation.h"

class ColorAnimation : public Animation {
public:
	ColorAnimation(
			AnimationContext &context,
			uint8_t red, uint8_t green, uint8_t blue,
			uint32_t duration);

	void run() override;
	void abort() override;

protected:
	void fillScreen();

	uint8_t r, g, b;
};
