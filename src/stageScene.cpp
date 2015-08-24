#include "system.h"
#include "scancode.h"
#include "iGameScene.h"
#include "texture.h"
#include "audioChunk.h"
#include "camera.h"
#include "tiledMap.h"

#include "stageScene.h"

#define CAMERA_W (16 * 20)
#define CAMERA_HI (16 * 20)

StageScene::StageScene():
	camera_(500, 500, CAMERA_W, CAMERA_HI),
	map_("asset/map/home.json"),
	bgTex_("./asset/image/stageBg.png", {0, 0, 500, 500})
{
	Rect sonStartPos = map_.getObjectPos("sonStartPoint");
	Rect dadStartPos = map_.getObjectPos("dadStartPoint");

	camera_.setWorldSize(map_.getPixelWidth(),
			     map_.getPixelHeight());

	son_.setPos(sonStartPos.x, sonStartPos.y);
	dad_.setPos(dadStartPos.x, dadStartPos.y);

	dad_.setSon(&son_);
}

void
StageScene::update()
{
	if (System::event().keyIsPressed(Scancode::Q))
		System::gameScene().popScene();

	if (System::event().keyIsPressed(Scancode::J))
		camera_.setY(camera_.getTop() + 5);

	if (System::event().keyIsPressed(Scancode::K))
		camera_.setY(camera_.getTop() - 5);

	if (System::event().keyIsPressed(Scancode::H))
		camera_.setX(camera_.getLeft() - 5);

	if (System::event().keyIsPressed(Scancode::L))
		camera_.setX(camera_.getLeft() + 5);

	for (auto& e : objectList_)
		e->update();

	//map_.update();
	son_.update();
	dad_.update();

	son_.takeDadsLoves(dad_.getMyLoves());
	dad_.takeSonsLove(son_.getMyLoves());
}

void
StageScene::render()
{
	static IRenderingSubsystem& rendering = System::rendering();

	rendering.setRenderDrawColor(0xcc, 0xcc, 0xcc, 0x00);
	rendering.renderClear();

	for (auto& e : objectList_)
		e->render(camera_);

	//map_.render(camera_);
	bgTex_.render();
	son_.render(camera_);
	dad_.render(camera_);

	rendering.renderPresent();
}
