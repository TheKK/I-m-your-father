#include <cmath>

#include "camera.h"
#include "system.h"
#include "scancode.h"

#include "son.h"

namespace
{
	int kSonWidth = 32;
	int kSonHeight = 32;

	int kCollideWidth = 16;
	int kCollideHeight = 32;

	float kJumpAcc = -2.0;
}

Son::Son():
	sonTexture_("asset/image/son.png", {0, 0, kSonWidth, kSonHeight}),
	sonWalk_("./asset/image/son_walk.png", {0, 0, kSonWidth, kSonHeight},
		 4, 5),
	sonStand_("./asset/image/son_stand.png", {0, 0, kSonWidth, kSonHeight},
		 13, 5),
	sonJump_("./asset/image/son_jump.png", {0, 0, kSonWidth, kSonHeight},
		 3, 5),
	sonAttack_("./asset/image/son_attack.png", {0, 0, kSonWidth, kSonHeight},
		 9, 5)
{
	posRect_.x = 0;
	posRect_.y = 0;
	posRect_.w = 32;
	posRect_.h = 32;

	animatedSprites_.emplace(State::Walking, &sonWalk_);
	animatedSprites_.emplace(State::Standing, &sonStand_);
	animatedSprites_.emplace(State::Jumpping, &sonJump_);
	animatedSprites_.emplace(State::Attacking, &sonAttack_);

	currentSprite_ = &sonStand_;
	currentState_ = State::Standing;
}

void
Son::update()
{
	/* Gravity */
	accY_ = 0.1;

	switch (currentState_) {
	case State::Standing:
		if (System::event().getKeyState(Scancode::LEFT)) {
			velX_ = -2;
			currentState_ = State::Walking;
			currentSprite_ = animatedSprites_[currentState_];
		} else if (System::event().getKeyState(Scancode::RIGHT)) {
			velX_ = 2;
			currentState_ = State::Walking;
			currentSprite_ = animatedSprites_[currentState_];
		} else {
			velX_ = 0;
		}

		if (System::event().keyIsPressed(Scancode::Z)) {
			accY_ += kJumpAcc;
			currentState_ = State::Jumpping;
			currentSprite_ = animatedSprites_[currentState_];
		} else if (System::event().keyIsPressed(Scancode::X)) {
			currentState_ = State::Attacking;
			currentSprite_ = animatedSprites_[currentState_];
			currentSprite_->setFrame(0);
		}
		break;

	case State::Jumpping:
		if (isOnGround_)
			currentState_ = State::Standing;
			currentSprite_ = animatedSprites_[currentState_];
		break;

	case State::Walking:
		if (System::event().getKeyState(Scancode::LEFT)) {
			velX_ = -2;
		} else if (System::event().getKeyState(Scancode::RIGHT)) {
			velX_ = 2;
		} else {
			velX_ = 0;
			currentState_ = State::Standing;
			currentSprite_ = animatedSprites_[currentState_];
		}

		if (System::event().keyIsPressed(Scancode::Z)) {
			accY_ += kJumpAcc;
			currentState_ = State::Jumpping;
			currentSprite_ = animatedSprites_[currentState_];
		} else if (System::event().keyIsPressed(Scancode::X)) {
			currentState_ = State::Attacking;
			currentSprite_ = animatedSprites_[currentState_];
			currentSprite_->setFrame(0);
		}
		break;

	case State::Attacking:
		static int frameCounter = 45;
		if (frameCounter == 0) {
			currentState_ = State::Standing;
			currentSprite_ = animatedSprites_[currentState_];
			frameCounter = 45;
		} else {
			--frameCounter;
		}
		break;

	default:
		break;
	}

	velX_ += accX_;
	velY_ += accY_;

	for (auto& e : collides_) {
		updateX_(*e);
		updateY_(*e);
		checkWallAround_(*e);
	}

	posX_ += velX_;
	posY_ += velY_;

	if (currentSprite_)
		currentSprite_->update();
}

void
Son::render(Camera& camera)
{
	static Rect drawDest;

	drawDest.x = posX_ - camera.getLeft();
	drawDest.y = posY_ - camera.getTop();
	drawDest.w = posRect_.w;
	drawDest.h = posRect_.h;

	if (currentSprite_)
		currentSprite_->render(drawDest);
}

void
Son::addCollide(ICollidable& object)
{
	collides_.push_back(&object);
}

void
Son::setPos(int x, int y)
{
	posX_ = x;
	posY_ = y;
}

void
Son::updateX_(ICollidable& collidable)
{
	Rect colliedRect;
	std::vector<Rect> tiles;

	if (velX_ > 0.f) {
		/* Test right part first */
		colliedRect.x = std::round(posX_ + kCollideWidth / 2 + velX_);
		colliedRect.y = std::round(posY_);
		colliedRect.w = std::round(kCollideWidth / 2);
		colliedRect.h = std::round(kCollideHeight);

		tiles = collidable.getCollideRects(colliedRect);

		for (const Rect& tile : tiles) {
			if (hasIntersection(tile, colliedRect)) {
				velX_ = 0.f;
				accX_ = 0.f;
				posX_ = tile.x - kCollideWidth;
			}
		}

		/* Test left then */
		colliedRect.x = std::round(posX_ + velX_);
		colliedRect.y = std::round(posY_);
		colliedRect.w = std::round(kCollideWidth / 2);
		colliedRect.h = std::round(kCollideHeight);

		tiles = collidable.getCollideRects(colliedRect);

		for (const Rect& tile : tiles) {
			if (hasIntersection(tile, colliedRect)) {
				velX_ = 0.0f;
				accX_ = 0.0f;
				posX_ = tile.x + tile.w;
			}
		}
	} else if (velX_ < 0) {
		/* Test left part first */
		colliedRect.x = std::round(posX_ + velX_);
		colliedRect.y = std::round(posY_);
		colliedRect.w = std::round(kCollideWidth / 2);
		colliedRect.h = std::round(kCollideHeight);

		tiles = collidable.getCollideRects(colliedRect);

		for (const Rect& tile : tiles) {
			if (hasIntersection(tile, colliedRect)) {
				velX_ = 0.0f;
				accX_ = 0.0f;
				posX_ = tile.x + tile.w;
			}
		}

		/* Test right part then */
		colliedRect.x = std::round(posX_ + kCollideWidth / 2 + velX_);
		colliedRect.y = std::round(posY_);
		colliedRect.w = std::round(kCollideWidth / 2);
		colliedRect.h = std::round(kCollideHeight);

		tiles = collidable.getCollideRects(colliedRect);

		for (const Rect& tile : tiles) {
			if (hasIntersection(tile, colliedRect)) {
				velX_ = 0.f;
				accX_ = 0.f;
				posX_ = tile.x - kCollideWidth;
			}
		}
	}
}

void
Son::updateY_(ICollidable& collidable)
{
	std::vector<Rect> tiles;
	Rect colliedRect;

	if (velY_ > 0.f) {
		/* Test botton part first */
		colliedRect.x = std::round(posX_);
		colliedRect.y = std::round(posY_ + kCollideHeight / 2 + velY_);
		colliedRect.w = std::round(kCollideWidth);
		colliedRect.h = std::round(kCollideHeight / 2);

		tiles = collidable.getCollideRects(colliedRect);

		for (const Rect& tile : tiles) {
			if (hasIntersection(tile, colliedRect)) {
				velY_ = 0.f;
				accY_ = 0.f;
				posY_ = tile.y - kCollideHeight;
			}
		}

		/* Test top part then */
		colliedRect.x = std::round(posX_);
		colliedRect.y = std::round(posY_ + velY_);
		colliedRect.w = std::round(kCollideWidth);
		colliedRect.h = std::round(kCollideHeight / 2);

		tiles = collidable.getCollideRects(colliedRect);

		for (const Rect& tile : tiles) {
			if (hasIntersection(tile, colliedRect)) {
				velY_ = 0.f;
				accY_ = 0.f;
				posY_ = tile.y + tile.h;
			}
		}
	} else if (velY_ < 0.f) {
		/* Test top part first */
		colliedRect.x = std::round(posX_);
		colliedRect.y = std::round(posY_ + velY_);
		colliedRect.w = std::round(kCollideWidth);
		colliedRect.h = std::round(kCollideHeight / 2);

		tiles = collidable.getCollideRects(colliedRect);

		for (const Rect& tile : tiles) {
			if (hasIntersection(tile, colliedRect)) {
				velY_ = 0.f;
				accY_ = 0.f;
				posY_ = tile.y + tile.h;
			}
		}

		/* Test botton part then */
		colliedRect.x = std::round(posX_);
		colliedRect.y = std::round(posY_ + kCollideHeight / 2 + velY_);
		colliedRect.w = std::round(kCollideWidth);
		colliedRect.h = std::round(kCollideHeight / 2);

		tiles = collidable.getCollideRects(colliedRect);

		for (const Rect& tile : tiles) {
			if (hasIntersection(tile, colliedRect)) {
				velY_ = 0.f;
				accY_ = 0.f;
				posY_ = tile.y - kCollideHeight;
			}
		}
	}
}


void
Son::checkWallAround_(ICollidable& collidable)
{
	std::vector<Rect> tiles;
	Rect colliedRect;

	/* Check if standing on floor */
	colliedRect.x = std::round(posX_);
	colliedRect.y = std::round(posY_ + kCollideHeight / 2) + 1;
	colliedRect.w = std::round(kCollideWidth);
	colliedRect.h = std::round(kCollideHeight / 2);

	tiles = collidable.getCollideRects(colliedRect);
	if (tiles.size() > 0)
		isOnGround_ = true;
	else
		isOnGround_ = false;
}
