#ifndef I_MOVEABLE_H
#define I_MOVEABLE_H
#pragma once

#include "rect.h"

class IMoveable
{
public:
	virtual ~IMoveable();

	virtual void setPos(int x, int y) = 0;
	virtual void setSize(int w, int h) = 0;

	virtual int getLeft() const = 0;
	virtual int getRight() const = 0;
	virtual int getTop() const = 0;
	virtual int getBottom() const = 0;
private:
	Rect posRect_;
	float realX_, realY_;
	float velX_, velY_;
	float accX_, accY_;
};

#endif /* I_MOVEABLE_H */
