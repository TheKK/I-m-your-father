#ifndef SON_H
#define SON_H
#pragma once

#include <vector>
#include <list>
#include <map>

#include "texture.h"
#include "rect.h"
#include "animatedSprite.h"
#include "audioChunk.h"

#include "iGameObject.h"
#include "iCollidable.h"

class Camera;

class Son : public IGameObject
{
public:
	Son();

	virtual void update();
	virtual void render(Camera& camera);

	void setPos(int x, int y) { posX_ = x; posY_ = y; }

	std::list<Rect> getMyLoves();
	void takeDadsLoves(std::list<Rect> loves);

	int getLife() { return lifePoint_; }

	Rect posRect_;
	float posX_, posY_;
private:
	struct Love {
		Rect posRect;
		float floatCounter;
	};

	Texture loveTexture_;
	Texture sonsLife_;
	AnimatedSprite sonSprite_;
	AnimatedSprite sonWalkRight_;
	AnimatedSprite sonWalkLeft_;

	AnimatedSprite* currentSprite_;

	AudioChunk getHitSe_;
	AudioChunk loveEmitSe_;

	int jummping_;

	int lifePoint_;

	int reloadCount_;
	int rehitCount_;
	int lotsOfLove_;

	std::list<Love> myLoves_;

	void emitMyLove_();
	void getHit_();
	bool isOnGround_();
	void renderChargeBar_();
	void renderSonsLife_();
};

#endif /* SON_H */
