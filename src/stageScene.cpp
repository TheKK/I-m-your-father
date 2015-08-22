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
	map_("asset/map/home.json")
{
	Rect sonStartPos = map_.getObjectPos("sonStartPoint");

	camera_.setWorldSize(map_.getPixelWidth(),
			     map_.getPixelHeight());

	son_.setPos(sonStartPos.x, sonStartPos.y);
	son_.addCollide(map_);
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

	map_.update();
	son_.update();
}

void
StageScene::render()
{
	static int x, y;
	static IEventSubsystem& event = System::event();
	static IRenderingSubsystem& rendering = System::rendering();

	event.getMousePosition(&x, &y);

	rendering.setRenderDrawColor(0xcc, 0xcc, 0xcc, 0x00);
	rendering.renderClear();

	for (auto& e : objectList_)
		e->render(camera_);

	map_.render(camera_);
	son_.render(camera_);

	rendering.setRenderDrawColor(0xff, 0x22, 0x14, 0x00);
	rendering.renderRect(x / 500. * CAMERA_W, y / 500. * CAMERA_HI,
			     25, 25);

	rendering.renderPresent();
}
