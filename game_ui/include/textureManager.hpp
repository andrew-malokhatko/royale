#pragma once

#include <unordered_map>
#include <future>
#include "CardType.hpp"
#include "raylib.h"

namespace ui
{
	class TextureManager
	{
		inline static size_t InstanceCount = 0;
		inline static std::unordered_map<royale::CardType, Image> Images {};
		inline static std::future<void> LoadedImages {};

	private:
		static void LoadImages();
		static void UnloadImages();

	public:
		TextureManager();
		~TextureManager();

		Image GetImage(royale::CardType card);
	};
}