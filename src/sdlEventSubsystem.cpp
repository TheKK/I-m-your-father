#include <SDL.h>
#include <cstdint>
#include <stdexcept>

#include "sdlEventSubsystem.h"
SDLEventSubsystem::SDLEventSubsystem()
{
	if (SDL_Init(SDL_INIT_EVENTS))
		throw std::runtime_error("sdl event subsystem init failed");

	printf("SDLEventSubsystem hi\n");
}

SDLEventSubsystem::~SDLEventSubsystem()
{
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	printf("SDLEventSubsystem bye\n");
}

int
SDLEventSubsystem::pollEvent()
{
	static SDL_Event event;

	for (auto& e : keyPressed_)
		e = false;

	for (auto& e : keyUnpressed_)
		e = false;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (!event.key.repeat)
				keyPressed_[event.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			if (!event.key.repeat)
				keyUnpressed_[event.key.keysym.scancode] = true;
			break;
		}
	}

	return 0;
}

bool
SDLEventSubsystem::keyIsPressed(uint8_t keycode)
{
	return keyPressed_[keycode];
}

bool
SDLEventSubsystem::keyIsUnpressed(uint8_t keycode)
{
	return keyUnpressed_[keycode];
}

bool
SDLEventSubsystem::getKeyState(uint8_t keycode)
{
	static const uint8_t* keyStates = SDL_GetKeyboardState(nullptr);

	return keyStates[keycode];
}

void
SDLEventSubsystem::getMousePosition(int* x, int* y)
{
	SDL_GetMouseState(x, y);
}
