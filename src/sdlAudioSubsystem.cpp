#include <SDL.h>
#include <stdexcept>
#include <string>

/* Feature from Emscripten, you have to use SDL_mixer from SDL1.X */
#ifdef __EMSCRIPTEN__
#include <SDL/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif

#include "../inc/sdlAudioSubsystem.h"

SDLAudioSubsystem::SDLAudioSubsystem(int frequency, uint16_t format,
				     int channels, int chunksize):
	chunkManager_([](const std::string& filePath) -> Mix_Chunk*
		      {
			      Mix_Chunk* chunkToReturn =
				      Mix_LoadWAV(filePath.c_str());

			      if (!chunkToReturn) {
				      std::string errMsg = "Mix error: " + std::string(Mix_GetError());
				      throw std::runtime_error(errMsg);
			      }

			      return chunkToReturn;
		      },
		      [](Mix_Chunk* ptr)
		      {
			      Mix_FreeChunk(ptr);
		      }
	)
{
	if (SDL_Init(SDL_INIT_AUDIO)) {
		std::string errMsg = "SDL error: " + std::string(SDL_GetError());
		throw std::runtime_error(errMsg);
	}

	if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3))
		printf("MIX warn: %s\n", Mix_GetError());

	if (Mix_OpenAudio(frequency, format, channels, chunksize)) {
		std::string errMsg = "Mix error: " + std::string(Mix_GetError());
		throw std::runtime_error(errMsg);
	}

	printf("SDLAudioSubsystem hi\n");
}

SDLAudioSubsystem::~SDLAudioSubsystem()
{
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	printf("SDLAudioSubsystem bye\n");
}

AudioChunkRaw
SDLAudioSubsystem::getAudioChunkRaw(const std::string& filePath)
{
	return chunkManager_.getResource(filePath);
}
void
SDLAudioSubsystem::playAudioChunkRaw(AudioChunkRaw chunk, int channel, int loops)
{
	Mix_PlayChannel(channel, chunk.get(), loops);
}

void
SDLAudioSubsystem::pauseChannel(int channel)
{
	Mix_Pause(channel);
}

void
SDLAudioSubsystem::resumeChannel(int channel)
{
	Mix_Resume(channel);
}

bool
SDLAudioSubsystem::channelPaused(int channel)
{
	return (Mix_Paused(channel) == 1);
}

bool
SDLAudioSubsystem::channelPlaying(int channel)
{
	return (Mix_Playing(channel) == 1);
}
