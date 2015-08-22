#ifndef PLAYGROUND_SCENE_H
#define PLAYGROUND_SCENE_H
#pragma once

#include <list>
#include <memory>

#include "system.h"
#include "scancode.h"
#include "iGameScene.h"
#include "texture.h"
#include "audioChunk.h"

class PlaygroundScene : public IGameScene
{
public:
	PlaygroundScene():
		bgTex_("bg.png", {0, 0, 500, 500}),
		weirdSe_("se.ogg")
	{
	}

	virtual void update()
	{
		for (auto& e : objectList_)
			e->update();

		if (System::event().keyIsPressed(Scancode::W))
			weirdSe_.play(-1, 0);

		if (System::event().keyIsPressed(Scancode::P))
			System::gameScene().pushScene<PlaygroundScene>();

		if (System::event().keyIsPressed(Scancode::O))
			System::gameScene().popScene();

		if (System::event().keyIsPressed(Scancode::S))
			System::gameScene().swapScene<PlaygroundScene>();
	}

	virtual void render()
	{
		static int x, y;
		static IEventSubsystem& event = System::event();
		static IRenderingSubsystem& rendering = System::rendering();

		event.getMousePosition(&x, &y);

		rendering.setRenderDrawColor(0xcc, 0xcc, 0xcc, 0x00);
		rendering.renderClear();

		for (auto& e : objectList_)
			e->render();

		bgTex_.render();

		rendering.setRenderDrawColor(0xff, 0x22, 0x14, 0x00);
		rendering.renderRect(x, y, 25, 25);

		rendering.renderPresent();
	}
private:
	Texture bgTex_;
	AudioChunk weirdSe_;
	std::list<IGameObject*> objectList_;
};

#endif /* PLAYGROUND_SCENE_H */
