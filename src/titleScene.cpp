#include "introScene.h"
#include "scancode.h"
#include "system.h"

#include "titleScene.h"

namespace
{
}

TitleScene::TitleScene():
	bgTex_("./asset/image/title.png", {0, 0, 500, 500}),
	enterSe_("./asset/sound/enterGame.ogg"),
	readyToSwapScene_(false)
{
}

void
TitleScene::update()
{
	if (!readyToSwapScene_ && System::event().keyIsPressed(Scancode::RETURN)) {
		readyToSwapScene_ = true;
		enterSe_.play(0, 0);
	}

	if (readyToSwapScene_ && !System::audio().channelPlaying(0))
		System::gameScene().swapScene<IntroScene>();
}

void
TitleScene::render()
{
	System::rendering().setRenderDrawColor(0x33, 0x33, 0x33, 0xff);
	System::rendering().renderClear();

	bgTex_.render();

	System::rendering().renderPresent();
}
