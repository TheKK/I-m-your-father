#include "rect.h"
#include "titleScene.h"
#include "system.h"
#include "scancode.h"

#include "endScene.h"

namespace
{
	const Rect kWindowRect = {0, 0, 500, 500};

	const Rect kPressButtonDest = {440, 470, 50, 20};
}

EndScene::EndScene():
	noDadTex_("./asset/image/noDad.png", kWindowRect),
	youreAManTex_("./asset/image/youreAMan.png", kWindowRect),
	buTex_("./asset/image/bu.png", kWindowRect),
	noTex_("./asset/image/no.png", kWindowRect),
	finTex_("./asset/image/fin.png", kWindowRect),
	notFinTex_("./asset/image/notFin.png", kWindowRect),
	okMonTex_("./asset/image/okMon.png", kWindowRect),
	noOneTex_("./asset/image/noOne.png", kWindowRect),
	realFinTex_("./asset/image/realFin.png", kWindowRect),
	pressButton_("./asset/image/pressButton1.png", {0, 0, 50, 20}, 2, 10),
	noDadSe_("./asset/sound/noDad.ogg"),
	youreAManSe_("./asset/sound/youreAMan.ogg"),
	buSe_("./asset/sound/bu.ogg"),
	noSe_("./asset/sound/no.ogg"),
	finSe_("./asset/sound/fin.ogg"),
	notFinSe_("./asset/sound/notFin.ogg"),
	okMonSe_("./asset/sound/okMon.ogg"),
	noOneSe_("./asset/sound/noOne.ogg"),
	realFinSe_("./asset/sound/realFin.ogg"),
	currentPage_(0)
{
	noDadSe_.play(0, 0);
}

void
EndScene::update()
{
	if (!System::audio().channelPlaying(0) &&
	    System::event().keyIsPressed(Scancode::RETURN)) {
		currentPage_++;

		switch (currentPage_) {
		case 1:
			youreAManSe_.play(0, 0);
			break;
		case 2:
			buSe_.play(0, 0);
			break;
		case 3:
			noSe_.play(0, 0);
			break;
		case 4:
			finSe_.play(0, 0);
			break;
		case 5:
			notFinSe_.play(0, 0);
			break;
		case 6:
			okMonSe_.play(0, 0);
			break;
		case 7:
			noOneSe_.play(0, 0);
			break;
		case 8:
			realFinSe_.play(0, 0);
			break;
		}
	}

	pressButton_.update();
}

void
EndScene::render()
{
	System::rendering().setRenderDrawColor(0x33, 0x33, 0x33, 0xff);
	System::rendering().renderClear();

	switch (currentPage_) {
	case 0:
		noDadTex_.render();
		break;
	case 1:
		youreAManTex_.render();
		break;
	case 2:
		buTex_.render();
		break;
	case 3:
		noTex_.render();
		break;
	case 4:
		finTex_.render();
		break;
	case 5:
		notFinTex_.render();
		break;
	case 6:
		okMonTex_.render();
		break;
	case 7:
		noOneTex_.render();
		break;
	case 8:
		realFinTex_.render();
		break;
	default:
		System::gameScene().swapScene<TitleScene>();
		break;
	}

	if (!System::audio().channelPlaying(0))
		pressButton_.render(kPressButtonDest);

	System::rendering().renderPresent();
}
