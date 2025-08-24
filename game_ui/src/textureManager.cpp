#include "textureManager.hpp"
#include "CardData.hpp"

namespace ui
{

	TextureManager::TextureManager()
	{
		LoadTextures();
	}

	TextureManager::~TextureManager()
	{
		UnloadTextures();
	}

	void TextureManager::LoadTextures()
	{
		for (auto& [card, str] : royale::STRING_FROM_CARD)
		{
			std::string fileName = std::format("assets/cards/{}.png", str);
			mTextures[card] = LoadTexture(fileName.c_str());
		}
	}

	void TextureManager::UnloadTextures()
	{
		for (auto& [type, texture] : mTextures)
		{
			UnloadTexture(texture);
		}
		mTextures.clear();
	}

	const TextureManager& TextureManager::getInstance()
	{
		static TextureManager instance;
		return instance;
	}


	//void TextureManager::ResizeCards(int width, int height)
	//{
	//	for (auto& [type, texture] : textures)
	//	{
	//		Image image = LoadImageFromTexture(texture);

	//		ImageResize(&image, width, height);

	//		UnloadTexture(texture);
	//		texture = LoadTextureFromImage(image);

	//		UnloadImage(image);
	//	}
	//}

	const Texture2D& TextureManager::getTexture(royale::CardType card) const
	{
		return mTextures.at(card);
	}

}