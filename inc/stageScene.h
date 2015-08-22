#ifndef STAGE_SCENE_H
#define STAGE_SCENE_H
#pragma once

#include <list>
#include <memory>

#include "iGameScene.h"
#include "camera.h"
#include "son.h"
#include "tiledMap.h"

class StageScene : public IGameScene
{
public:
	StageScene();

	virtual void update();
	virtual void render();
private:
	Camera camera_;
	TiledMap map_;
	Son son_;
	std::list<IGameObject*> objectList_;
};

#endif /* STAGE_SCENE_H */
