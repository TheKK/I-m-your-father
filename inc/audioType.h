#ifndef AUDIO_TYPE_H
#define AUDIO_TYPE_H
#pragma once

#include <memory>

#ifdef __EMSCRIPTEN__
#include <SDL/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif

typedef std::shared_ptr<Mix_Chunk> AudioChunkRaw;

#endif /* AUDIO_TYPE_H */
