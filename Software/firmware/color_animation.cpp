#include "color_animation.h"

ColorAnimation::ColorAnimation(
			AnimationContext &context,
			uint8_t red, uint8_t green, uint8_t blue,
			uint32_t duration)
	: Animation{context, duration},
	r{red}, g{green}, b{blue}
{
}

void ColorAnimation::run()
{
	fillScreen();
	context.delay(duration);
}

void ColorAnimation::fillScreen() {
	Rect sz = context.displaySize();	
	for(int x = sz.x; x < sz.width; x++) {
		for(int y = sz.y; y < sz.height; y++) {
			context.drawPixel(x, y, r, g, b);
		}
	}
	context.show();
}

void ColorAnimation::abort()
{
	// Nothing to do here
}

