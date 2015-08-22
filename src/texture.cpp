#include "system.h"

#include "texture.h"

Texture::Texture(const std::string& filePath, const Rect& clipRect):
	tex_(System::rendering().getTextureRaw(filePath)),
	clipRect_(clipRect)
{
}

void
Texture::load(const std::string& filePath, const Rect& clipRect)
{
	tex_ = System::rendering().getTextureRaw(filePath);
	clipRect_ = clipRect;
}

void
Texture::render(const Rect& posRect)
{
	System::rendering().renderTextureRaw(tex_, clipRect_, posRect);
}

void
Texture::render()
{
	System::rendering().renderTextureRawFullScreen(tex_, clipRect_);
}
