#ifndef SDL_RENDERING_SUBSYSTEM
#define SDL_RENDERING_SUBSYSTEM
#pragma once

#include <string>
#include <SDL.h>

#include "texture.h"
#include "rect.h"
#include "resourceManager.h"
#include "system.h"

class SDLRenderingSubsystem : public IRenderingSubsystem
{
public:
	SDLRenderingSubsystem(int windowWidth, int windowHeight,
			      const std::string& windowTitle);
	virtual ~SDLRenderingSubsystem();

	virtual int setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b,
				       uint8_t a);
	virtual int renderClear();
	virtual int renderPresent();

	virtual void renderRect(int x, int y, int w, int h);

	virtual void setLogicalRenderSize(int w, int h);
	virtual void getLogicalRenderSize(int* w, int* h);

	virtual TextureRaw getTextureRaw(const std::string& filePath);
	virtual void renderTextureRaw(TextureRaw& texture, const Rect& clipRect,
				      const Rect& posRect);
	virtual void renderTextureRawFullScreen(TextureRaw& texture,
						const Rect& clipRect);
private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	ResourceManager<SDL_Texture> textureManager_;
};

#endif /* SDL_RENDERING_SUBSYSTEM */
