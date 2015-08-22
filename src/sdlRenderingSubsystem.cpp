#include <stdexcept>
#include <string>
#include <memory>

#include <SDL_image.h>

#include "sdlRenderingSubsystem.h"

SDLRenderingSubsystem::SDLRenderingSubsystem(int windowWidth, int windowHeight,
					     const std::string& windowTitle):
	textureManager_(
		[this](const std::string& filePath) -> SDL_Texture* {
			return IMG_LoadTexture(renderer_, filePath.c_str());
		},
		[](SDL_Texture* tex) {
			SDL_DestroyTexture(tex);
		}
	)
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::string errMsg = "SDL error: " + std::string(SDL_GetError());
		throw std::runtime_error(errMsg);
	}

	window_ = SDL_CreateWindow(
		windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight,
		SDL_WINDOW_SHOWN);
	if (!window_) {
		throw std::runtime_error("failed while creating window");
	}

	renderer_ = SDL_CreateRenderer(
		window_,
		-1,
		SDL_RENDERER_ACCELERATED);
	if (!renderer_) {
		throw std::runtime_error("failed while creating renderer");
	}

	SDL_RenderSetLogicalSize(renderer_, windowWidth, windowHeight);

	if (IMG_Init(IMG_INIT_PNG) < 0) {
		throw std::runtime_error("failed while initializing SDL_image");
	}

	printf("SDLRenderingSubsystem hi\n");
}

SDLRenderingSubsystem::~SDLRenderingSubsystem()
{
	if (window_)
		SDL_DestroyWindow(window_);

	if (renderer_)
		SDL_DestroyRenderer(renderer_);

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	IMG_Quit();

	printf("SDLRenderingSubsystem bye\n");
}

int
SDLRenderingSubsystem::setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(renderer_, r, g, b, a);

	return 0;
}

int
SDLRenderingSubsystem::renderClear()
{
	SDL_RenderClear(renderer_);

	return 0;
}

int
SDLRenderingSubsystem::renderPresent()
{
	SDL_RenderPresent(renderer_);

	return 0;
}

void
SDLRenderingSubsystem::renderRect(int x, int y, int w, int h)
{
	static SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_RenderDrawRect(renderer_, &rect);
}

void
SDLRenderingSubsystem::setLogicalRenderSize(int w, int h)
{
	SDL_RenderSetLogicalSize(renderer_, w, h);
}

void
SDLRenderingSubsystem::getLogicalRenderSize(int* w, int* h)
{
	SDL_RenderGetLogicalSize(renderer_, w, h);
}

TextureRaw
SDLRenderingSubsystem::getTextureRaw(const std::string& filePath)
{
	return textureManager_.getResource(filePath);
}

void
SDLRenderingSubsystem::renderTextureRaw(TextureRaw& texture,
					const Rect& clipRect,
					const Rect& posRect)
{
	SDL_Rect sdlClipRect = {
		.x = clipRect.x,
		.y = clipRect.y,
		.w = clipRect.w,
		.h = clipRect.h
	};
	SDL_Rect sdlPosRect = {
		.x = posRect.x,
		.y = posRect.y,
		.w = posRect.w,
		.h = posRect.h
	};

	SDL_RenderCopy(renderer_, texture.get(), &sdlClipRect, &sdlPosRect);
}

void
SDLRenderingSubsystem::renderTextureRawFullScreen(TextureRaw& texture,
					const Rect& clipRect)
{
	SDL_Rect sdlClipRect = {
		.x = clipRect.x,
		.y = clipRect.y,
		.w = clipRect.w,
		.h = clipRect.h
	};

	SDL_RenderCopy(renderer_, texture.get(), &sdlClipRect, nullptr);
}
