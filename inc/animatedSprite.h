#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H
#pragma once

#include <string>

#include "rect.h"
#include "textureRaw.h"

class Graphics;

/*
 * TODO Currently this only accept horizontal sprite,
 * need to be more flexible
 */
class AnimatedSprite
{
public:
	AnimatedSprite(const std::string& filePath,
		       const Rect& startClipRect, int frameNum, int period);
	~AnimatedSprite();

	void load(const std::string& filePath,
		  const Rect& startClipRect, int frameNum, int period);

	void update();
	void render(const Rect& dstRect);

	void setFrame(int which)
	{
		if ((which < 0) || (which >= totoalFrameNum_))
			return;
		else
			currentFrame_ = which;
	}
private:
	TextureRaw spriteSheet_;
	Rect startClipRect_;
	Rect drawClipRect_;

	int totoalFrameNum_;
	int currentFrame_;

	int periodMax_;
	int periodCounter_;
};
#endif /* ANIMATED_SPRITE_H */
