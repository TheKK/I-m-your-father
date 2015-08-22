#ifndef SDL_EVENT_SUBSYSTEM
#define SDL_EVENT_SUBSYSTEM
#pragma once

#include <cstdint>

#include "system.h"
#include "scancode.h"

class SDLEventSubsystem : public IEventSubsystem
{
public:
	SDLEventSubsystem();
	virtual ~SDLEventSubsystem();

	virtual int pollEvent();

	virtual bool keyIsPressed(uint8_t keycode);
	virtual bool keyIsUnpressed(uint8_t keycode);
	virtual bool getKeyState(uint8_t keycode);
	virtual void getMousePosition(int* x, int* y);
private:
	bool keyPressed_[Scancode::NUM_SCANCODES] = {false};
	bool keyUnpressed_[Scancode::NUM_SCANCODES] = {false};
};

#endif /* SDL_EVENT_SUBSYSTEM */
