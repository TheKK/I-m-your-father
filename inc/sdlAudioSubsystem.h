#ifndef SDL_AUDIO_SUBSYSTEM_H
#define SDL_AUDIO_SUBSYSTEM_H
#pragma once

#include <string>
#include <cstdint>

#include "resourceManager.h"
#include "system.h"

class SDLAudioSubsystem : public IAudioSubsystem
{
public:
	SDLAudioSubsystem(int frequency, uint16_t format, int channels,
			  int chunksize);
	virtual ~SDLAudioSubsystem();

	virtual AudioChunkRaw getAudioChunkRaw(const std::string& filePath);
	virtual void playAudioChunkRaw(AudioChunkRaw chunk, int channel,
				       int loops);
	virtual void pauseChannel(int channel);
	virtual void resumeChannel(int channel);
	virtual bool channelPaused(int channel);
	virtual bool channelPlaying(int channel);
private:
	ResourceManager<Mix_Chunk> chunkManager_;
};

#endif /* SDL_AUDIO_SUBSYSTEM_H */
