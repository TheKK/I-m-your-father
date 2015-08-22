#ifndef AUDIO_CHUNK_H
#define AUDIO_CHUNK_H
#pragma once

#include "audioType.h"

class AudioChunk
{
public:
	AudioChunk();
	AudioChunk(const std::string& filePath);

	void load(const std::string& filePath);
	void play(int channel, int loops);
private:
	AudioChunkRaw chunk_;
};

#endif /* AUDIO_CHUNK_H */
