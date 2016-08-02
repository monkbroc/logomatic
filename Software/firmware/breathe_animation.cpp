#include "breathe_animation.h"

uint8_t BreatheAnimation::delay = 10;

// A value going up and down from 255 to 0 and back
class Breathe {
public:
	Breathe() : value(255), direction(-1) {}
	void next() {
		if (direction == -1 && value == 0) {
			direction = 1;
		} else if(direction == 1 && value == 255) {
			direction = -1;
		}
		value += direction;
	}

	uint8_t get() {
		return value;
	}

protected:
	uint8_t value;
	uint8_t direction;
};

BreatheAnimation::BreatheAnimation(
			AnimationContext &context,
			uint8_t red, uint8_t green, uint8_t blue,
			uint32_t duration)
	: Animation{context, duration},
	r{red}, g{green}, b{blue}
{
}

void BreatheAnimation::run()
{
	uint32_t start = context.now();
	Breathe brightness;
	
	while(context.now() - start < duration) {
		if(_abort) return;

		brightness.next();
		fillScreen(brightness.get());
		context.delay(delay);
	}
}

void BreatheAnimation::fillScreen(uint8_t brightness) {
	Rect sz = context.displaySize();	
	for(int x = sz.x; x < sz.width; x++) {
		for(int y = sz.y; y < sz.height; y++) {
			context.drawPixel(x, y,
					(r * brightness) / 256,
					(g * brightness) / 256,
					(b * brightness) / 256);
		}
	}
	context.show();
}

void BreatheAnimation::abort()
{
	_abort = true;
}

