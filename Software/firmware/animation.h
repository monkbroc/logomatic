#include <cstdint>

#include "rect.h"

class AnimationContext {
public:
	virtual Rect displaySize() = 0;
	virtual void clear() = 0;
	virtual void show() = 0;
	virtual void drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) = 0;
	virtual void delay(uint32_t millis) = 0;
	virtual uint32_t now() = 0;
};

class Animation {
public:
	Animation(AnimationContext &context, uint32_t duration) :
		context{context},
		duration{duration}
	{}
	virtual ~Animation() {}

	virtual void run() = 0;
	virtual void abort() = 0;

protected:
	AnimationContext &context;
	uint32_t duration;
};
