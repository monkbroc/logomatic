#include "ColorAnimation.h"

ColorAnimation::ColorAnimation(
			AnimationContext &context,
			Color color,
			uint32_t duration)
	: Animation{context, duration},
	color{color}
{
}

void ColorAnimation::run()
{
	fillScreen();
	context.wait(duration, &_abort);
}

void ColorAnimation::fillScreen() {
	Rect sz = context.displaySize();	
	for(int x = sz.x; x < sz.width; x++) {
		for(int y = sz.y; y < sz.height; y++) {
			context.drawPixel(x, y, color.red, color.green, color.blue);
		}
	}
	context.show();
}

