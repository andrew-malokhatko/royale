#pragma once

#include <array>
#include "unitType.hpp"
#include "raylib.h"


class TextureManager
{
public:
	inline static std::array<Texture2D, royale::UNIT_COUNT> textures {};

	static void LoadTextures()
	{
		textures[royale::None] = LoadTexture("cards/none.png");
		textures[royale::Knight] = LoadTexture("cards/knight.png");
		textures[royale::Bomber] = LoadTexture("cards/bomber.png");
		textures[royale::Prince] = LoadTexture("cards/prince.png");
		textures[royale::Goblins] = LoadTexture("cards/goblins.png");
		textures[royale::Archers] = LoadTexture("cards/archers.png");
		textures[royale::Giant] = LoadTexture("cards/giant.png");

	}
	
	static void UnloadTextures()
	{
		for (Texture2D& texture : textures)
		{
			UnloadTexture(texture);
		}
	}

	// resizes the cards ignoring the aspect ratio
	static void ResizeCards(int width, int height)
	{
		for (Texture2D& texture : textures)
		{
			Image image = LoadImageFromTexture(texture);

			ImageResize(&image, width, height);

			UnloadTexture(texture);
			texture = LoadTextureFromImage(image);

			UnloadImage(image);
		}
	}

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

	//static TextureManager* getInstance()
	//{
	//	if (mTextureManagerInstance)
	//	{
	//		return mTextureManagerInstance;
	//	}

	//	mTextureManagerInstance = new TextureManager();

	//	return mTextureManagerInstance;
	//}
};
