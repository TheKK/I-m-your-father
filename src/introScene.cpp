#include "rect.h"
#include "stageScene.h"
#include "system.h"
#include "scancode.h"

#include "manualScene.h"

namespace
{
	const Rect kWindowRect = {0, 0, 500, 500};

	const Rect kPressButtonDest = {440, 470, 50, 20};
}

ManualScene::ManualScene():
	manualTex_("./asset/image/manual.png", kWindowRect),
	pressButton_("./asset/image/pressButton.png", {0, 0, 50, 20}, 2, 10),
	currentPage_(0)
{
}

void
ManualScene::update()
{
	if (!System::audio().channelPlaying(0) &&
	    System::event().keyIsPressed(Scancode::RETURN)) {
		currentPage_++;
	}

	pressButton_.update();
}

void
ManualScene::render()
{
	System::rendering().setRenderDrawColor(0x33, 0x33, 0x33, 0xff);
	System::rendering().renderClear();

	switch (currentPage_) {
	case 0:
		manualTex_.render();
		break;
	default:
		System::gameScene().swapScene<StageScene>();
		break;
	}

	if (!System::audio().channelPlaying(0))
		pressButton_.render(kPressButtonDest);

	System::rendering().renderPresent();
}
