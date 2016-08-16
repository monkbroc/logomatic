#include "DualColorAnimation.h"
#include "PixelMapping.h"

DualColorAnimation::DualColorAnimation(
			AnimationContext &context,
			Color centerColor,
			Color arrowColor,
			uint32_t duration)
	: Animation{context, duration},
	centerColor{centerColor},
	arrowColor{arrowColor}
{
}

void DualColorAnimation::run()
{
	fillScreen();
	context.wait(duration, &_abort);
}

void DualColorAnimation::fillScreen() {
	Rect sz = context.displaySize();	
	for(int x = sz.x; x < sz.width; x++) {
		for(int y = sz.y; y < sz.height; y++) {
            Color color;
            if (isArrowPixel(x, y)) {
                color = arrowColor;
            } else if(isCenterPixel(x, y)) {
                color = centerColor;
            }

			context.drawPixel(x, y, color.red, color.green, color.blue);
		}
	}
	context.show();
}

