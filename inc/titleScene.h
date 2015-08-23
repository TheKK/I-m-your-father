#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H
#pragma once

#include <list>
#include <memory>

#include "texture.h"
#include "audioChunk.h"

#include "iGameScene.h"

class TitleScene : public IGameScene
{
public:
	TitleScene();

	virtual void update();
	virtual void render();
private:
	Texture bgTex_;

	AudioChunk enterSe_;

	bool readyToSwapScene_;
};

#endif /* TITLE_SCENE_H */
