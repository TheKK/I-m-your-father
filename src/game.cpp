#include <cassert>
#include <SDL.h>

#include "scancode.h"
#include "stageScene.h"
#include "titleScene.h"
#include "endScene.h"

#include "game.h"

Game::Game()
{
	System::gameScene().pushScene<TitleScene>();
	gameScene_ = System::gameScene().topScene();
}

void
Game::update()
{
	static IEventSubsystem& event = System::event();

	gameScene_ = System::gameScene().topScene();
	if (!gameScene_)
		exit();

	event.pollEvent();

	if (event.keyIsPressed(Scancode::Q))
		exit();

	if (gameScene_)
		gameScene_->update();
}

void
Game::render()
{
	if (gameScene_)
		gameScene_->render();
}
