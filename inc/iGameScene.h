#ifndef I_GAME_SCENE_H
#define I_GAME_SCENE_H
#pragma once

#include <list>
#include <memory>

class IGameScene
{
public:
	virtual ~IGameScene() {};

	virtual void update() = 0;
	virtual void render() = 0;
};

#endif /* I_GAME_SCENE_H */
