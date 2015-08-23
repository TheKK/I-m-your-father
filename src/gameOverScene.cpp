#include "titleScene.h"
#include "scancode.h"
#include "system.h"

#include "gameOverScene.h"

namespace
{
}

GameOverScene::GameOverScene():
	bgTex_("./asset/image/gameover.png", {0, 0, 500, 500}),
	byeSe_("./asset/sound/gameover.ogg")
{
	byeSe_.play(0, 0);
}

void
GameOverScene::update()
{
	if (!System::audio().channelPlaying(0))
		System::gameScene().swapScene<TitleScene>();
}

void
GameOverScene::render()
{
	System::rendering().setRenderDrawColor(0x33, 0x33, 0x33, 0xff);
	System::rendering().renderClear();

	bgTex_.render();

	System::rendering().renderPresent();
}
