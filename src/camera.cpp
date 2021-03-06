#include <algorithm>

#include "system.h"

#include "camera.h"

Camera::Camera()
{
}

Camera::Camera(int worldWidth, int worldHeight, int viewWidth, int viewHeight)
{
	setup(worldWidth, worldHeight, viewWidth, viewHeight);
}

Camera::~Camera()
{
}

void
Camera::setup(int worldWidth, int worldHeight, int viewWidth, int viewHeight)
{
	worldRect_ = {
		0, 0,
		worldWidth, worldHeight
	};

	viewRect_ = {
		0, 0,
		viewWidth, viewHeight
	};

	deadZoneRect_ = {
		viewRect_.w / 2 - 40 / 2, viewRect_.h / 2 - 40 / 2,
		40, 40
	};

	System::rendering().setLogicalRenderSize(viewWidth, viewHeight);
}

void
Camera::update()
{
	/* Not use for now */
	return;

	int deadZoneLeft, deadZoneRight, deadZoneTop, deadZoneBottom;
	int targetLeft, targetRight, targetTop, targetBottom;
	int dx, dy;
	//Rect targetRect_ = target_->posRectOnMap();

	deadZoneLeft = viewRect_.x + deadZoneRect_.x;
	deadZoneRight = viewRect_.x + deadZoneRect_.x + deadZoneRect_.w;
	deadZoneTop = viewRect_.y + deadZoneRect_.y;
	deadZoneBottom = viewRect_.y + deadZoneRect_.y + deadZoneRect_.h;

	//targetLeft = targetRect_.x;
	//targetRight = targetRect_.x + targetRect_.w;
	//targetTop = targetRect_.y;
	//targetBottom = targetRect_.y + targetRect_.h;

	if (targetLeft < deadZoneLeft)
		dx = targetLeft - deadZoneLeft;
	else if (targetRight > deadZoneRight)
		dx = targetRight - deadZoneRight;
	else
		dx = 0;

	if (targetTop < deadZoneTop)
		dy = targetTop - deadZoneTop;
	else if (targetBottom > deadZoneBottom)
		dy = targetBottom - deadZoneBottom;
	else
		dy = 0;

	viewRect_.x += dx;
	viewRect_.y += dy;

	viewRect_.x = std::max(viewRect_.x, 0);
	viewRect_.x = std::min(viewRect_.x, worldRect_.w - viewRect_.w);
	viewRect_.y = std::max(viewRect_.y, 0);
	viewRect_.y = std::min(viewRect_.y, worldRect_.h - viewRect_.h);
}

void
Camera::setWorldSize(int w, int h)
{
	worldRect_.w = w;
	worldRect_.h = h;
}

void
Camera::setX(int x)
{
	viewRect_.x = std::min(std::max(x, 0), worldRect_.w - viewRect_.w);
}

void
Camera::setY(int y)
{
	viewRect_.y = std::min(std::max(y, 0), worldRect_.h - viewRect_.h);
}

int
Camera::getLeft() const
{
	return viewRect_.x;
}

int
Camera::getRight() const
{
	return viewRect_.x + viewRect_.w - 1;
}

int
Camera::getTop() const
{
	return viewRect_.y;
}

int
Camera::getBottom() const
{
	return viewRect_.y + viewRect_.h - 1;
}
