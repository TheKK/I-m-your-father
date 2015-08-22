#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <memory>
#include <string>

#include "textureRaw.h"
#include "rect.h"

#include "iGameObject.h"

class Texture
{
public:
	Texture() {};
	Texture(const std::string& filePath, const Rect& clipRect);

	void load(const std::string& filePath, const Rect& clipRect);
	void render(const Rect& posRect);
	void render();
private:
	TextureRaw tex_;
	Rect clipRect_;
};

#endif /* TEXTURE_H */
