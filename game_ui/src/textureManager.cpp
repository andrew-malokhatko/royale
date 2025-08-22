#include "textureManager.hpp"
#include "CardData.hpp"

TextureManager::TextureManager()
{
	instances++;
}

TextureManager::~TextureManager()
{
	instances--;
	if (instances == 0)
	{
		UnloadTextures();
	}
}

void TextureManager::LoadTextures()
{
	for (auto& [card, str] : royale::STRING_FROM_CARD)
	{
		std::string fileName = std::format("assets/cards/{}.png", str);
		textures[card] = LoadTexture(fileName.c_str());
	}
}

void TextureManager::UnloadTextures()
{

	for (auto& [type, texture] : textures)
	{
		UnloadTexture(texture);
	}
	textures.clear();
}

void TextureManager::ResizeCards(int width, int height)
{
	for (auto& [type, texture] : textures)
	{
		Image image = LoadImageFromTexture(texture);

		ImageResize(&image, width, height);

		UnloadTexture(texture);
		texture = LoadTextureFromImage(image);

		UnloadImage(image);
	}
}

const Texture2D& TextureManager::GetTexture(royale::CardType card)
{
	return textures.at(card);
}