#include "system.h"

GameSceneSubsystem::GameSceneSubsystem()
{
	assert(!instance_);

	instance_ = this;

	printf("GameSceneSubsystem hi\n");
}

GameSceneSubsystem::~GameSceneSubsystem()
{
	printf("GameSceneSubsystem bye\n");
}

IGameScene* GameSceneSubsystem::topScene()
{
	if (needPop_) {
		gameSceneStack_.pop();
		needPop_ = false;
	}

	if (needSwap_) {
		std::unique_ptr<IGameScene> tmp;

		tmp = std::move(gameSceneStack_.top());
		gameSceneStack_.pop();
		gameSceneStack_.pop();
		gameSceneStack_.emplace(std::move(tmp));

		needSwap_ = false;
	}

	if (gameSceneStack_.size() == 0)
		return nullptr;

	return gameSceneStack_.top().get();
}

void
GameSceneSubsystem::popScene()
{
	needPop_ = true;
}
