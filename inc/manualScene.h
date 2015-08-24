#ifndef MANUAL_SCENE_H
#define MANUAL_SCENE_H
#pragma once

#include "iGameScene.h"
#include "texture.h"
#include "animatedSprite.h"

class ManualScene : public IGameScene
{
public:
	ManualScene();

	virtual void update();
	virtual void render();
private:
	Texture manualTex_;

	AnimatedSprite pressButton_;

	int currentPage_;
};

#endif /* MANUAL_SCENE_H */
