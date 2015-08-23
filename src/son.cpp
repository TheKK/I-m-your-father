#include <cmath>

#include "camera.h"
#include "system.h"
#include "scancode.h"
#include "gameOverScene.h"

#include "son.h"

namespace
{
	const int kSonWidth = 16;
	const int kSonHeight = 32;
	const float kSonSpeed = 2;

	const int kReloadFrame = 300;
	const int kRehitFrame = 30;

	const int kLoveWidth = 16;
	const int kLoveHeight = 16;
	const float kLoveSpeed = -2;
	const int kMaxLoveCount = 60;

	const int kLifeWidth = 16;
	const int kLifeHeight = 16;
	const int kLifeStartX = 0;
	const int kLifeStartY = 16 * 19;

	const int kJumpFrame = 15;
	const int kJumpSpeed = -3;
}

Son::Son():
	loveTexture_("./asset/image/love.png", {0, 0, kLoveWidth, kLoveHeight}),
	sonsLife_("./asset/image/sons_life.png", {0, 0, kSonWidth, kSonHeight}),
	sonSprite_("./asset/image/son.png", {0, 0, kSonWidth, kSonHeight}, 8, 5),
	sonWalkRight_("./asset/image/son_walk_right.png", {0, 0, kSonWidth, kSonHeight}, 4, 5),
	sonWalkLeft_("./asset/image/son_walk_left.png", {0, 0, kSonWidth, kSonHeight}, 4, 5),
	getHitSe_("./asset/sound/sonHit1.ogg"),
	loveEmitSe_("./asset/sound/sonEmitLove.ogg"),
	jummping_(0),
	lifePoint_(5),
	reloadCount_(kReloadFrame),
	rehitCount_(0),
	lotsOfLove_(0)
{
	posRect_.x = 0;
	posRect_.y = 0;
	posRect_.w = kSonWidth;
	posRect_.h = kSonHeight;

	currentSprite_ =  &sonSprite_;
}

void
Son::update()
{
	if (reloadCount_)
		reloadCount_--;

	if (rehitCount_)
		rehitCount_--;

	if (jummping_) {
		jummping_--;
		posY_ += kJumpSpeed;
	} else {
		posY_ -= kJumpSpeed;
	}

	if (lotsOfLove_) {
		lotsOfLove_--;
		emitMyLove_();
	}

	if (System::event().keyIsPressed(Scancode::X)) {
		if (reloadCount_ == 0) {
			reloadCount_ = kReloadFrame;
			lotsOfLove_ = kMaxLoveCount;
		}
	}

	if (System::event().keyIsPressed(Scancode::Z)) {
		if ((jummping_ == 0) && isOnGround_())
			jummping_ = kJumpFrame;
	}

	/* Change to walking animated sprite */
	if (System::event().keyIsPressed(Scancode::LEFT))
		currentSprite_ = &sonWalkLeft_;
	if (System::event().keyIsPressed(Scancode::RIGHT))
		currentSprite_ = &sonWalkRight_;

	/* Change to standing animation sprite */
	if (System::event().keyIsUnpressed(Scancode::LEFT))
		currentSprite_ = &sonSprite_;
	if (System::event().keyIsUnpressed(Scancode::RIGHT))
		currentSprite_ = &sonSprite_;

	if (System::event().getKeyState(Scancode::RIGHT))
		posX_ += kSonSpeed;
	if (System::event().getKeyState(Scancode::LEFT))
		posX_ -= kSonSpeed;

	/* Simple collide */
	posX_ = std::min(std::max((int) posX_, 16), 16 * 19 - kSonWidth);
	posY_ = std::min(std::max((int) posY_, 16), 16 * 19 - kSonHeight);

	for (auto& e : myLoves_) {
		e.floatCounter += 0.1;
		e.posRect.y += kLoveSpeed;
	}

	myLoves_.remove_if(
		[](Love& love)
		   {
			   static Rect worldRect = {0, 0, 16 * 20, 16 * 20};
			   return !hasIntersection(love.posRect, worldRect);
		   });

	if (lifePoint_ == 0)
		System::gameScene().swapScene<GameOverScene>();

	if (currentSprite_)
		currentSprite_->update();
}

void
Son::render(Camera& camera)
{
	static Rect drawDest;

	drawDest.w = kLoveWidth;
	drawDest.h = kLoveHeight;

	for (auto& e : myLoves_) {
		drawDest.x = e.posRect.x - camera.getLeft() + sin(e.floatCounter) * 10;
		drawDest.y = e.posRect.y - camera.getTop();
		loveTexture_.render(drawDest);
	}

	drawDest.x = posX_ - camera.getLeft();
	drawDest.y = posY_ - camera.getTop();
	drawDest.w = posRect_.w;
	drawDest.h = posRect_.h;

	if (currentSprite_)
		currentSprite_->render(drawDest);

	renderSonsLife_();
	renderChargeBar_();
}

std::list<Rect>
Son::getMyLoves()
{
	std::list<Rect> loves;

	for (auto& e : myLoves_)
		loves.push_back(e.posRect);

	return loves;
}

void
Son::takeDadsLoves(std::list<Rect> loves)
{
	/* Not now */
	if (rehitCount_)
		return;

	posRect_.x = posX_;
	posRect_.y = posY_;

	for (auto& love : loves) {
		if (hasIntersection(posRect_, love)) {
			getHit_();
			return;
		}
	}
}

void
Son::emitMyLove_()
{
	Love love;

	loveEmitSe_.play(-1, 0);

	love.posRect = {(int) posX_, (int) posY_, kLoveWidth, kLoveHeight};
	love.floatCounter = 0;

	myLoves_.push_front(love);
}

void
Son::getHit_()
{
	getHitSe_.play(-1, 0);
	rehitCount_ = kRehitFrame;
	lifePoint_--;
}

bool
Son::isOnGround_()
{
	return ((int) posY_ >= 16 * 19 - kSonHeight);
}

void
Son::renderChargeBar_()
{
	System::rendering().setRenderDrawColor(0xcc, 0xcc, 0xcc, 0xff);
	System::rendering().renderFillRect(
		(int) posX_, (int) (posY_ + kSonHeight),
		kSonWidth,
		5);

	if (reloadCount_)
		System::rendering().setRenderDrawColor(0x00, 0xff, 0x11, 0xff);
	else
		System::rendering().setRenderDrawColor(0x11, 0x11, 0xff, 0xff);

	System::rendering().renderFillRect(
		(int) posX_, (int) (posY_ + kSonHeight),
		kSonWidth * (kReloadFrame -  reloadCount_) / kReloadFrame,
		5);

}

void
Son::renderSonsLife_()
{
	static Rect lifeDest = {0, kLifeStartY, kLifeWidth, kLifeHeight};

	for (int i = 0; i < lifePoint_; ++i) {
		lifeDest.x = kLifeStartX + kLifeWidth * i;

		sonsLife_.render(lifeDest);
	}
}
