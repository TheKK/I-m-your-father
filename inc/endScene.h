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
	Texture noDadTex_, youreAManTex_, buTex_, noTex_, finTex_, notFinTex_,
		okMonTex_, noOneTex_, realFinTex_;

	AudioChunk noDadSe_, youreAManSe_, buSe_, noSe_, finSe_, notFinSe_,
		okMonSe_, noOneSe_, realFinSe_;

	int currentPage_;
};

#endif /* END_SCENE_H */
