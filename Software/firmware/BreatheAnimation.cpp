#include "BreatheAnimation.h"
#include "application.h"

uint8_t BreatheAnimation::delay = 1;

// A value going up and down from 255 to 0 and back
class Breathe {
public:
    static const int MAX = 255;
	Breathe() : value(0), direction(1) {}
	void next() {
		if (direction == -1 && value == 0) {
			direction = 1;
		} else if(direction == 1 && value == MAX) {
			direction = -1;
		}
		value += direction;
	}

	uint8_t get() {
		return (uint8_t) value;
	}

    bool isMin() {
        return value == 0;
    }

protected:
	int value;
	int direction;
};

BreatheAnimation::BreatheAnimation(
			AnimationContext &context,
			Color color,
			uint32_t duration)
	: Animation{context, duration},
	color{color}
{
}

void BreatheAnimation::run()
{
	uint32_t start = context.now();
	Breathe brightness;
	
	while(context.now() - start < duration) {
        // Serial.printlnf("Breathing %d,%d,%d", color.red, color.green, color.blue);
        do {
            if(_abort) return;

            brightness.next();
            fillScreen(brightness.get());
            context.wait(delay, &_abort);
        } while(!brightness.isMin());
	}
}

void BreatheAnimation::fillScreen(uint8_t brightness) {
	Rect sz = context.displaySize();	
	for(int x = sz.x; x < sz.width; x++) {
		for(int y = sz.y; y < sz.height; y++) {
			context.drawPixel(x, y, color.red, color.green, color.blue, brightness);
		}
	}
	context.show();
}

