#ifndef GAME_H
#define GAME_H

#include <memory>
#include <list>

#include "iGameScene.h"
#include "system.h"

class IGameObject;

class Game
{
public:
	Game();

	void update();
	void render();

	bool isRunning() { return isRunning_; }
	void exit() { isRunning_ = false; }
private:
	bool isRunning_ = true;

	IGameScene* gameScene_ = nullptr;
};

#endif /* GAME_H */
