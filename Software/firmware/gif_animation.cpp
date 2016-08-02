#include "gif_animation.h"
#include "string.h"

GifAnimation::GifAnimation(
			AnimationContext &context,
			char *filename,
			uint32_t duration)
	: Animation{context, duration}
{
	this->filename = new char[strlen(filename)];
	strcpy(this->filename, filename);
}

GifAnimation::~GifAnimation() {
	delete[] filename;
}

void GifAnimation::run()
{
	context.delay(duration);
}

void GifAnimation::abort()
{
	_abort = true;
}

