#include <stdexcept>

#include "system.h"

#include "animatedSprite.h"

AnimatedSprite::AnimatedSprite(const std::string& filePath,
			       const Rect& startClipRect, int frameNum,
			       int period):
	spriteSheet_(System::rendering().getTextureRaw(filePath)),
	startClipRect_(startClipRect),
	drawClipRect_(startClipRect),
	totoalFrameNum_(frameNum),
	currentFrame_(0),
	periodMax_(period),
	periodCounter_(0)
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void
AnimatedSprite::load(const std::string& filePath,
		     const Rect& startClipRect, int frameNum, int period)
{
	spriteSheet_ = System::rendering().getTextureRaw(filePath);

	startClipRect_ = startClipRect;
	drawClipRect_ = startClipRect;

	totoalFrameNum_ = frameNum;
	periodMax_ = period;
	periodCounter_ = 0;
}
void
AnimatedSprite::update()
{
	++periodCounter_;
	if (periodCounter_ == periodMax_) {
		periodCounter_ = 0;

		++currentFrame_;
		if (currentFrame_ == totoalFrameNum_)
			currentFrame_ = 0;

		drawClipRect_.x = (startClipRect_.x +
				   startClipRect_.w * currentFrame_);
	}
}

void
AnimatedSprite::render(const Rect& dstRect)
{
	System::rendering().renderTextureRaw(spriteSheet_,
					     drawClipRect_, dstRect);
}
