#pragma once

#include <array>
#include "card.hpp"
#include "raylib.h"


class TextureManager
{
public:
	inline static std::array<Texture2D, royale::CARD_COUNT> textures {};

	static void LoadTextures()
	{
		textures[toIndex(royale::Card::None)] = LoadTexture("cards/none.png");
		textures[toIndex(royale::Card::Arrows)] = LoadTexture("cards/arrows.png");
		textures[toIndex(royale::Card::Bomber)] = LoadTexture("cards/bomber.png");
		textures[toIndex(royale::Card::Knight)] = LoadTexture("cards/knight.png");
		textures[toIndex(royale::Card::Giant)] = LoadTexture("cards/giant.png");
		textures[toIndex(royale::Card::Goblins)] = LoadTexture("cards/goblins.png");
		textures[toIndex(royale::Card::Golem)] = LoadTexture("cards/golem.png");
		textures[toIndex(royale::Card::Prince)] = LoadTexture("cards/prince.png");
		textures[toIndex(royale::Card::Princess)] = LoadTexture("cards/princess.png");
		textures[toIndex(royale::Card::XBow)] = LoadTexture("cards/x_bow.png");
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

	static const Texture2D& GetTexture(royale::Card card)
	{
		return textures[toIndex(card)];
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
