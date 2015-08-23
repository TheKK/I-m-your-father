#include <cmath>

#include "camera.h"
#include "system.h"
#include "scancode.h"
#include "endScene.h"
#include "son.h"

#include "dad.h"

namespace
{
	const Rect kWorldRect = {0, 0, 16 * 20, 16 * 20};
	const Rect kNoneWallRect = {16, 16, 16 * 18, 16 * 18};

	const int kDadWidth = 32;
	const int kDadHeight = 32;
	const float kDadSpeed = 3;

	const int kReloadFrame = 10;
	const int kRehitFrame = 1;

	const int kFirstFormLoveWidth = 3;
	const int kFirstFormLoveHeight = 32;
	const float kFirstFormLoveSpeedY = 4;

	const int kThunderBallWidth = 16;
	const int kThunderBallHeight = 16;
	const float kThunderBallSpeedX = 8;
	const float kThunderBallSpeedY = 4;
	const int kFormTwoMoveFrame = 10;

	/* TODO Make it 100 after realease */
	const int kMaxHp = 100;

	const int kTotalFormNum = 2;
	const int kLoveEmitCoolDown[] = {10, 60};
}

Dad::Dad():
	loveTexture_("./asset/image/dads_love.png", {0, 0, kFirstFormLoveWidth, kFirstFormLoveHeight}),
	dadSprite_("./asset/image/dad.png", {0, 0, kDadWidth, kDadHeight}, 1, 10),
	getHitSe_("./asset/sound/dadHit1.ogg"),
	loveEmitSe_("./asset/sound/dadEmitLove.ogg"),
	dadsTalk_("./asset/sound/dadsTalk.ogg"),
	lifePoint_(kMaxHp),
	rehitCount_(0),
	currentForm_(0),
	loveEmitCoolDown_(kLoveEmitCoolDown[0])
{
	posRect_.x = 0;
	posRect_.y = 0;
	posRect_.w = kDadWidth;
	posRect_.h = kDadHeight;
}

void
Dad::update()
{
	if (rehitCount_)
		rehitCount_--;

	if (loveEmitCoolDown_)
		loveEmitCoolDown_--;
	
	switch (currentForm_) {
	case 0:
		if (loveEmitCoolDown_ == 0) {
			emitMyLove_(0);
			loveEmitCoolDown_ = kLoveEmitCoolDown[0];
		}
		break;
	case 1:
		if (loveEmitCoolDown_ == 0) {
			emitMyLove_(1);
			loveEmitCoolDown_ = kLoveEmitCoolDown[1];
		}
		break;
	default:
		break;
	}

	for (auto& e : myLoves_)
		e->update();

	myLoves_.remove_if([](std::unique_ptr<DadsLove>& love)
			   {
				   return love->dead();
			   });
}

void
Dad::render(Camera& camera)
{
	static Rect drawDest;

	for (auto& e : myLoves_)
		e->render(camera);

	drawDest.x = posX_ - camera.getLeft();
	drawDest.y = posY_ - camera.getTop();
	drawDest.w = posRect_.w;
	drawDest.h = posRect_.h;

	dadSprite_.render(drawDest);
	drawHpBar_();
}


std::list<Rect>
Dad::getMyLoves()
{
	std::list<Rect> listToReturn;

	for (auto& e : myLoves_)
		for (auto& box : e->getHitBox())
			listToReturn.push_back(box);

	return listToReturn;
}
void
Dad::takeSonsLove(std::list<Rect> loves)
{
	if (rehitCount_)
		return;

	posRect_.x = posX_;
	posRect_.y = posY_;

	for (auto& love : loves) {
		if (hasIntersection(posRect_, love)) {
			getHit_();
			break;
		}
	}
}

void
Dad::emitMyLove_(int form)
{
	switch (form) {
	case 0:
		myLoves_.emplace_back(new Dad::DadsLoveFormOne(this));
		break;
	case 1:
		myLoves_.emplace_back(new Dad::DadsLoveFormTwo(this));
		break;
	default:
		break;
	}
}

void
Dad::getHit_()
{
	getHitSe_.play(1, 0);
	rehitCount_ = kRehitFrame;
	lifePoint_ = std::max(0, lifePoint_ - 1);

	if (lifePoint_ == 0) {
		if (currentForm_ + 1 < kTotalFormNum)
			currentForm_++;
		else /* You won */
			System::gameScene().swapScene<EndScene>();

		dadsTalk_.play(-1, 0);
		lifePoint_ = kMaxHp;
		rehitCount_ = 180;
		loveEmitCoolDown_ = kLoveEmitCoolDown[currentForm_];
	}
}

void
Dad::drawHpBar_()
{
	System::rendering().setRenderDrawColor(0x00, 0xff, 0x11, 0xff);
	System::rendering().renderFillRect((int) posX_, (int) (posY_ + kDadHeight),
					   kDadWidth * (float) lifePoint_ / kMaxHp,
					   5);
}

Dad::DadsLoveFormOne::DadsLoveFormOne(Dad* dad):
	dad_(dad),
	loveTex_("./asset/image/dads_love.png", {0, 0, kFirstFormLoveWidth, kFirstFormLoveHeight}),
	posRect_({(int) dad->posX_, (int) dad->posY_, kFirstFormLoveWidth, kFirstFormLoveHeight})
{
	dad->loveEmitSe_.play(-1, 0);
	dad->posX_ = 16 + rand() % (16 * 18);
}

std::list<Rect>
Dad::DadsLoveFormOne::getHitBox()
{
	std::list<Rect> listToReturn(1, posRect_);

	return  listToReturn;
}

void
Dad::DadsLoveFormOne::update()
{
	posRect_.y += kFirstFormLoveSpeedY;
}

void
Dad::DadsLoveFormOne::render(Camera& camera)
{
	static Rect drawDest = {0, 0, kFirstFormLoveWidth, kFirstFormLoveHeight};

	drawDest.x = posRect_.x - camera.getLeft();
	drawDest.y = posRect_.y - camera.getTop();

	loveTex_.render(drawDest);
}

bool
Dad::DadsLoveFormOne::dead()
{
	return !hasIntersection(posRect_, kWorldRect);
}

Dad::DadsLoveFormTwo::DadsLoveFormTwo(Dad* dad):
	dad_(dad),
	thunderBallTex_("./asset/image/dad_thunderBall.png",
			{0, 0, kThunderBallWidth, kThunderBallHeight}, 5, 10),
	emitSe_("./asset/sound/thunderBallEmit.ogg"),
	exploedSe_("./asset/sound/thunderBallExplode.ogg"),
	leftPosRect_({(int) dad->posX_, (int) dad->posY_, kThunderBallWidth, kThunderBallHeight}),
	rightPosRect_({(int) dad->posX_, (int) dad->posY_, kThunderBallWidth, kThunderBallHeight}),
	moveFrameCounter_(kFormTwoMoveFrame),
	hasExplode_(false),
	hasEmit_(false)
{
	float targetPosX_ = dad->son_->posX_;

	movePerFrame_ = (targetPosX_ - dad->posX_) / kFormTwoMoveFrame;

	leftPosRect_.x = targetPosX_;
	leftPosRect_.y = dad->posY_;
	rightPosRect_.x = targetPosX_;
	rightPosRect_.y = dad->posY_;
}

std::list<Rect>
Dad::DadsLoveFormTwo::getHitBox()
{
	std::list<Rect> listToReturn;

	listToReturn.push_back(leftPosRect_);
	listToReturn.push_back(rightPosRect_);

	return  listToReturn;
}

void
Dad::DadsLoveFormTwo::update()
{
	if (moveFrameCounter_) {
		dad_->posX_ += movePerFrame_;
		moveFrameCounter_--;
		return;
	}

	if (leftPosRect_.y < 16 * 18) {
		if (!hasEmit_) {
			emitSe_.play(-1, 0);
			hasEmit_ = true;
		}

		leftPosRect_.y += kThunderBallSpeedY;
		rightPosRect_.y += kThunderBallSpeedY;
	} else {
		if (!hasExplode_) {
			exploedSe_.play(-1, 0);
			hasExplode_ = true;
		}

		leftPosRect_.x -= kThunderBallSpeedX;
		rightPosRect_.x += kThunderBallSpeedX;
	}

	thunderBallTex_.update();
}

void
Dad::DadsLoveFormTwo::render(Camera& camera)
{
	static Rect drawDest = {0, 0, kThunderBallWidth, kThunderBallHeight};

	if (!hasEmit_)
		return;

	drawDest.x = leftPosRect_.x - camera.getLeft();
	drawDest.y = leftPosRect_.y - camera.getTop();

	thunderBallTex_.render(drawDest);

	drawDest.x = rightPosRect_.x - camera.getLeft();
	drawDest.y = rightPosRect_.y - camera.getTop();

	thunderBallTex_.render(drawDest);
}

bool
Dad::DadsLoveFormTwo::dead()
{
	return (!hasIntersection(leftPosRect_, kWorldRect) &&
		!hasIntersection(rightPosRect_, kWorldRect));
}
