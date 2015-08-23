#ifndef END_SCENE_H
#define END_SCENE_H
#pragma once

#include "iGameScene.h"
#include "texture.h"
#include "audioChunk.h"

class EndScene : public IGameScene
{
public:
	EndScene();

	virtual void update();
	virtual void render();
private:
	int currentPage_;
};

#endif /* END_SCENE_H */
