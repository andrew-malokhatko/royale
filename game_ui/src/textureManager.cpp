#include "TextureManager.hpp"
#include "CardData.hpp"

namespace ui
{
	TextureManager::TextureManager()
	{
		if (InstanceCount == 0)
			LoadImages();

		InstanceCount++;
	}

	TextureManager::~TextureManager()
	{
		InstanceCount--;

		if (InstanceCount == 0)
			UnloadImages();
	}

	void TextureManager::LoadImages()
	{
		LoadedImages = std::async(std::launch::async, []() {
			for (auto& [card, str] : royale::STRING_FROM_CARD)
			{
				std::string fileName = std::format("assets/cards/{}.png", str);
				Images[card] = LoadImage(fileName.c_str());
			}
		});
	}

	void TextureManager::UnloadImages()
	{
		assert(LoadedImages.valid());
		LoadedImages.wait();

		for (auto& [type, texture] : Images)
		{
			UnloadImage(texture);
		}
		Images.clear();
	}

	Image TextureManager::GetImage(royale::CardType card)
	{
		assert(LoadedImages.valid());
		LoadedImages.wait();

		return ImageCopy(Images.at(card));
	}
}