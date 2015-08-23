#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "rect.h"

class Camera
{
public:
	Camera();
	Camera(int worldWidth, int worldHeight, int viewWidth, int viewHeight);
	~Camera();

	void setup(int worldWidth, int worldHeight,
		   int viewWidth, int viewHeight);

	void update();

	void setWorldSize(int w, int h);

	void setX(int x);
	void setY(int y);

	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;

	Rect& getViewRect() { return viewRect_; }
	Rect& getWorldRect() { return worldRect_; }
private:
	Rect worldRect_;
	Rect viewRect_;
	Rect deadZoneRect_;
};

#endif /* CAMERA_H */
