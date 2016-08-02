#pragma once

#include "animation.h"

class GifAnimation : public Animation {
public:
	GifAnimation(
			AnimationContext &context,
			char *filename,
			uint32_t duration);
	~GifAnimation();

	void run() override;
	void abort() override;

protected:
	bool _abort;

	char *filename;
};
