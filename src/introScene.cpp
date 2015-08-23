#include "rect.h"
#include "stageScene.h"
#include "system.h"
#include "scancode.h"

#include "introScene.h"

namespace
{
	const Rect kWindowRect = {0, 0, 500, 500};

	const Rect kPressButtonDest = {440, 470, 50, 20};
}

IntroScene::IntroScene():
	houseTex_("./asset/image/house.png", kWindowRect),
	roomTex_("./asset/image/room.png", kWindowRect),
	dadsWorryFaceTex_("./asset/image/dadsWorryFace.png", kWindowRect),
	sonsAngerTex_("./asset/image/sonsAnger.png", kWindowRect),
	dadsSadFaceTex_("./asset/image/dadsSadFace.png", kWindowRect),
	sonsQuestionFaceTex_("./asset/image/sonsQuestionFace.png", kWindowRect),
	dadsFormOneTex_("./asset/image/dadsFormOne.png", kWindowRect),
	dadsFormTwoTex_("./asset/image/dadsFormTwo.png", kWindowRect),
	dadsFinalFormTex_("./asset/image/dadsFianlForm.png", kWindowRect),
	manualTex_("./asset/image/manual.png", kWindowRect),
	pressButton_("./asset/image/pressButton.png", {0, 0, 50, 20}, 2, 10),
	birdTweetSe_("./asset/sound/birdTweet.ogg"),
	whyYouHereSe_("./asset/sound/whyYouHere.ogg"),
	imSorrySe_("./asset/sound/imSorry.ogg"),
	youMonsterSe_("./asset/sound/youMonster.ogg"),
	whatYouSaidSe_("./asset/sound/whatYouSaid.ogg"),
	iSaidAgainSe_("./asset/sound/iSaidAgain.ogg"),
	howDidYouKnowSe_("./asset/sound/howDidYouKnow.ogg"),
	whatDoYouMeanSe_("./asset/sound/whatDoYouMean.ogg"),
	dadFormOneSe_("./asset/sound/dadFormOne.ogg"),
	ahhSe_("./asset/sound/ahh.ogg"),
	youHaveToDieSe_("./asset/sound/youHaveToDie.ogg"),
	currentPage_(0)
{
	birdTweetSe_.play(0, 0);
}

void
IntroScene::update()
{
	if (!System::audio().channelPlaying(0) &&
	    System::event().keyIsPressed(Scancode::RETURN)) {
		currentPage_++;

		switch (currentPage_) {
		case 1:
			whyYouHereSe_.play(0, 0);
			break;
		case 2:
			imSorrySe_.play(0, 0);
			break;
		case 3:
			youMonsterSe_.play(0, 0);
			break;
		case 4:
			whatYouSaidSe_.play(0, 0);
			break;
		case 5:
			iSaidAgainSe_.play(0, 0);
			break;
		case 6:
			howDidYouKnowSe_.play(0, 0);
			break;
		case 7:
			whatDoYouMeanSe_.play(0, 0);
			break;
		case 8:
			dadFormOneSe_.play(0, 0);
			break;
		case 9:
			ahhSe_.play(0, 0);
			break;
		case 10:
			youHaveToDieSe_.play(0, 0);
			break;
		}
	}

	pressButton_.update();
}

void
IntroScene::render()
{
	System::rendering().setRenderDrawColor(0x33, 0x33, 0x33, 0xff);
	System::rendering().renderClear();

	switch (currentPage_) {
	case 0:
		houseTex_.render();
		break;
	case 1:
		roomTex_.render();
		break;
	case 2:
		dadsWorryFaceTex_.render();
		break;
	case 3:
		sonsAngerTex_.render();
		break;
	case 4:
		dadsSadFaceTex_.render();
		break;
	case 5:
		sonsAngerTex_.render();
		break;
	case 6:
		dadsSadFaceTex_.render();
		break;
	case 7:
		sonsQuestionFaceTex_.render();
		break;
	case 8:
		dadsFormOneTex_.render();
		break;
	case 9:
		dadsFormTwoTex_.render();
		break;
	case 10:
		dadsFinalFormTex_.render();
		break;
	case 11:
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
