#include "system.h"

#include "audioChunk.h"

AudioChunk::AudioChunk()
{
}

AudioChunk::AudioChunk(const std::string& filePath):
	chunk_(System::audio().getAudioChunkRaw(filePath))
{
}

void
AudioChunk::load(const std::string& filePath)
{
	chunk_ = System::audio().getAudioChunkRaw(filePath);
}

void
AudioChunk::play(int channel, int loops)
{
	System::audio().playAudioChunkRaw(chunk_, channel, loops);
}
