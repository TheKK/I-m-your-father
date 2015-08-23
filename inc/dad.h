#ifndef DAD_H
#define DAD_H
#pragma once

#include <vector>
#include <memory>
#include <list>
#include <map>

#include "texture.h"
#include "rect.h"
#include "animatedSprite.h"
#include "audioChunk.h"

#include "iGameObject.h"
#include "iCollidable.h"

class Camera;

class Son;

class Dad : public IGameObject
{
public:
	Dad();

	virtual void update();
	virtual void render(Camera& camera);

	void setSon(Son* son) { son_ = son; }
	void setPos(int x, int y) { posX_ = x; posY_ = y; }

	std::list<Rect> getMyLoves();
	void takeSonsLove(std::list<Rect> loves);
private:
	class DadsLove
	{
	public:
		virtual ~DadsLove() {}

		virtual std::list<Rect> getHitBox() = 0;
		virtual void update() = 0;
		virtual void render(Camera& camera) = 0;
		virtual bool dead() = 0;
	};

	class DadsLoveFormOne : public DadsLove
	{
	public:
		DadsLoveFormOne(Dad* dad);

		virtual std::list<Rect> getHitBox();
		virtual void update();
		virtual void render(Camera& camera);
		virtual bool dead();
	private:
		Dad* dad_;
		Texture loveTex_;
		Rect posRect_;
	};

	class DadsLoveFormTwo : public DadsLove
	{
	public:
		DadsLoveFormTwo(Dad* dad);

		virtual std::list<Rect> getHitBox();
		virtual void update();
		virtual void render(Camera& camera);
		virtual bool dead();
	private:
		Dad* dad_;
		AnimatedSprite thunderBallTex_;
		AudioChunk emitSe_;
		AudioChunk exploedSe_;
		Rect leftPosRect_;
		Rect rightPosRect_;
		float movePerFrame_;
		int moveFrameCounter_;
		bool hasExplode_;
		bool hasEmit_;
	};

	Son* son_;

	Texture loveTexture_;
	AnimatedSprite dadSprite_;

	AudioChunk getHitSe_;
	AudioChunk loveEmitSe_;
	AudioChunk dadsTalk_;

	int lifePoint_;

	int rehitCount_;
	int currentForm_;
	int loveEmitCoolDown_;

	Rect posRect_;
	float posX_, posY_;

	std::list<std::unique_ptr<DadsLove>> myLoves_;

	void emitMyLove_(int form);
	void getHit_();
	void drawHpBar_();
};

#endif /* DAD_H */
