#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H
#pragma once

#include <list>
#include <memory>

#include "texture.h"
#include "audioChunk.h"

#include "iGameScene.h"

class GameOverScene : public IGameScene
{
public:
	GameOverScene();

	virtual void update();
	virtual void render();
private:
	Texture bgTex_;

	AudioChunk byeSe_;
};

#endif /* GAME_OVER_SCENE_H */
