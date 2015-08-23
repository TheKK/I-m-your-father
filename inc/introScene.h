#ifndef INTRO_SCENE_H
#define INTRO_SCENE_H
#pragma once

#include "iGameScene.h"
#include "texture.h"
#include "audioChunk.h"

class IntroScene : public IGameScene
{
public:
	IntroScene();

	virtual void update();
	virtual void render();
private:
	Texture houseTex_, roomTex_, dadsWorryFaceTex_, sonsAngerTex_,
		dadsSadFaceTex_, sonsQuestionFaceTex_, dadsFormOneTex_,
		dadsFormTwoTex_, dadsFinalFormTex_;

	AudioChunk birdTweetSe_, whyYouHereSe_, imSorrySe_, youMonsterSe_,
		   whatYouSaidSe_, iSaidAgainSe_, howDidYouKnowSe_,
		   whatDoYouMeanSe_, dadFormOneSe_, ahhSe_, youHaveToDieSe_;

	int currentPage_;
};

#endif /* INTRO_SCENE_H */
