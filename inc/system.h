#ifndef SYSTEM_H
#define SYSTEM_H
#pragma once

#include <cstdint>
#include <cassert>
#include <memory>
#include <string>
#include <stack>
#include <type_traits>

#include "textureRaw.h"
#include "audioType.h"
#include "rect.h"
#include "iGameScene.h"

class IRenderingSubsystem
{
public:
	IRenderingSubsystem()
	{
		assert (!instance_);

		instance_ = this;
	}

	virtual ~IRenderingSubsystem() {}

	virtual int setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b,
				       uint8_t a) = 0;
	virtual int renderClear() = 0;
	virtual int renderPresent() = 0;

	virtual void renderRect(int x, int y, int w, int h) = 0;

	virtual void setLogicalRenderSize(int w, int h) = 0;
	virtual void getLogicalRenderSize(int* w, int* h) = 0;

	virtual TextureRaw getTextureRaw(const std::string& filePath) = 0;
	virtual void renderTextureRaw(TextureRaw& texture, const Rect& clipRect,
				      const Rect& posRect) = 0;
	virtual void renderTextureRawFullScreen(TextureRaw& texture,
						const Rect& clipRect) = 0;
private:
	static IRenderingSubsystem* instance_;
};

class IEventSubsystem
{
public:
	IEventSubsystem() {
		assert (!instance_);

		instance_ = this;
	}
	virtual ~IEventSubsystem() {}

	virtual int pollEvent() = 0;

	virtual bool keyIsPressed(uint8_t code) = 0;
	virtual bool keyIsUnpressed(uint8_t code) = 0;
	virtual bool getKeyState(uint8_t code) = 0;
	virtual void getMousePosition(int* x, int* y) = 0;
private:
	static IEventSubsystem* instance_;
};

class IAudioSubsystem
{
public:
	IAudioSubsystem()
	{
		assert (!instance_);

		instance_ = this;
	}
	virtual ~IAudioSubsystem() {}

	virtual AudioChunkRaw getAudioChunkRaw(const std::string& filePath) = 0;
	virtual void playAudioChunkRaw(AudioChunkRaw chunk, int channel,
				       int loops) = 0;
	virtual void pauseChannel(int channel) = 0;
	virtual void resumeChannel(int channel) = 0;
	virtual bool channelPaused(int channel) = 0;
	virtual bool channelPlaying(int channel) = 0;
private:
	static IAudioSubsystem* instance_;
};

class GameSceneSubsystem
{
public:
	GameSceneSubsystem();
	~GameSceneSubsystem();

	IGameScene* topScene();

	template<typename T>
	void pushScene()
	{
		static_assert(std::is_base_of<IGameScene, T>::value,
			      "You could only push game scene");

		gameSceneStack_.emplace(new T());
	}

	template<typename T>
	void swapScene()
	{
		if (!needSwap_) {
			needSwap_ = true;
			gameSceneStack_.emplace(new T());
		}
	}

	void popScene();
private:
	static GameSceneSubsystem* instance_;

	bool needPop_ = false;
	bool needSwap_ = false;
	std::stack<std::unique_ptr<IGameScene>> gameSceneStack_;
};

/* TODO More secure instance retrieve */
class System
{
public:
	System(IRenderingSubsystem* renderingSubsystem,
	       IEventSubsystem* eventSubsystem,
	       IAudioSubsystem* audioSubsystem):
		renderingSubsystem_(renderingSubsystem),
		eventSubsystem_(eventSubsystem),
		audioSubsystem_(audioSubsystem)

	{
		assert(!instance_);

		instance_ = this;

		printf("System hi\n");
	}

	~System()
	{
		printf("System bye\n");
	}

	static System& instance()
	{
		return *instance_;
	}

	static IRenderingSubsystem& rendering()
	{
		return *instance_->renderingSubsystem_;
	}

	static IEventSubsystem& event()
	{
		return *instance_->eventSubsystem_;
	}

	static IAudioSubsystem& audio()
	{
		return *instance_->audioSubsystem_;
	}

	static GameSceneSubsystem& gameScene()
	{
		return instance_->gameSceneSubsystem_;
	}
private:
	static System* instance_;

	std::unique_ptr<IRenderingSubsystem> renderingSubsystem_;
	std::unique_ptr<IEventSubsystem> eventSubsystem_;
	std::unique_ptr<IAudioSubsystem> audioSubsystem_;

	GameSceneSubsystem gameSceneSubsystem_;
};

#endif /* SYSTEM_H */
