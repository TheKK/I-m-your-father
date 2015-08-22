#include "sdlRenderingSubsystem.h"
#include "sdlEventSubsystem.h"
#include "sdlAudioSubsystem.h"

#include "systemFactory.h"

namespace SystemFactory
{

System*
build(const std::string& configFile)
{
	IRenderingSubsystem* renderingSubsystem(
		new SDLRenderingSubsystem(500, 500, "hahahaha"));
	IEventSubsystem* eventSubsystem(new SDLEventSubsystem());
	IAudioSubsystem* audioSubsystem(
		new SDLAudioSubsystem(44100, MIX_DEFAULT_FORMAT, 2, 1024));

	return new System(renderingSubsystem, eventSubsystem, audioSubsystem);
}

}
