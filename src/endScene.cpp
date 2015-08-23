#include "rect.h"
#include "titleScene.h"
#include "system.h"
#include "scancode.h"

#include "endScene.h"

namespace
{
	const Rect kWindowRect = {0, 0, 500, 500};
}

EndScene::EndScene():
	currentPage_(-1)
{
}

void
EndScene::update()
{
	//if (!System::audio().channelPlaying(0) &&
	    //System::event().keyIsPressed(Scancode::RETURN)) {
		//currentPage_++;

		//switch (currentPage_) {
		//case 0:
			//birdTweetSe_.play(0, 0);
			//break;
		//case 1:
			//whyYouHereSe_.play(0, 0);
			//break;
		//case 2:
			//imSorrySe_.play(0, 0);
			//break;
		//case 3:
			//youMonsterSe_.play(0, 0);
			//break;
		//case 4:
			//whatYouSaidSe_.play(0, 0);
			//break;
		//case 5:
			//iSaidAgainSe_.play(0, 0);
			//break;
		//case 6:
			//howDidYouKnowSe_.play(0, 0);
			//break;
		//case 7:
			//whatDoYouMeanSe_.play(0, 0);
			//break;
		//case 8:
			//dadFormOneSe_.play(0, 0);
			//break;
		//case 9:
			//ahhSe_.play(0, 0);
			//break;
		//case 10:
			//youHaveToDieSe_.play(0, 0);
			//break;
		//}
	//}
}

void
EndScene::render()
{
	System::rendering().setRenderDrawColor(0x33, 0x33, 0x33, 0xff);
	System::rendering().renderClear();

	//switch (currentPage_) {
	//case -1:
		//break;
	//case 0:
		//houseTex_.render();
		//break;
	//case 1:
		//roomTex_.render();
		//break;
	//case 2:
		//dadsWorryFaceTex_.render();
		//break;
	//case 3:
		//sonsAngerTex_.render();
		//break;
	//case 4:
		//dadsSadFaceTex_.render();
		//break;
	//case 5:
		//sonsAngerTex_.render();
		//break;
	//case 6:
		//dadsSadFaceTex_.render();
		//break;
	//case 7:
		//sonsQuestionFaceTex_.render();
		//break;
	//case 8:
		//dadsFormOneTex_.render();
		//break;
	//case 9:
		//dadsFormTwoTex_.render();
		//break;
	//case 10:
		//dadsFinalFormTex_.render();
		//break;
	//default:
		//System::gameScene().swapScene<StageScene>();
		//break;
	//}

	System::rendering().renderPresent();
}
