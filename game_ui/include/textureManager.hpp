#pragma once

#include <unordered_map>
#include "CardType.hpp"
#include "raylib.h"


class TextureManager
{
	inline static std::unordered_map<royale::CardType, Texture2D> textures{};
	inline static bool initialized = false;
	inline static size_t instances = 0;

private:
	void UnloadTextures();

public:
	TextureManager();
	~TextureManager();

	void LoadTextures();

	// resizes the cards ignoring the aspect ratio
	void ResizeCards(int width, int height);
	const Texture2D& GetTexture(royale::CardType card);




#if 0
	// resizes the cards keeping the aspect ratio
	static void ResizeCards(int width, int height)
	{
		for (Texture2D& texture : textures) 
		{
			Image image = LoadImageFromTexture(texture);

			// TODO
			// remove when all textures are inserted in the textures array
			if (image.width == 0 || image.height == 0)
			{
				continue;
			}

			float originalWidth = image.width;
			float originalHeight = image.height;

			float scaleX = width / originalWidth;
			float scaleY = height / originalHeight;
			float scale = fminf(scaleX, scaleY);

			int newWidth = originalWidth * scale;
			int newHeight = originalHeight * scale;

			ImageResize(&image, newWidth, newHeight);

			UnloadTexture(texture);
			texture = LoadTextureFromImage(image);

			UnloadImage(image);
		}
	}
#endif
};
