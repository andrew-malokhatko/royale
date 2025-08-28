#pragma once

#include <unordered_map>
#include "CardType.hpp"
#include "raylib.h"

namespace ui
{
	class TextureManager
	{
		inline static std::unordered_map<royale::CardType, Texture2D> mTextures{};

	private:
		TextureManager();
		~TextureManager();

		void UnloadTextures();
		void LoadTextures();

	public:
		static const TextureManager& getInstance();
		const Texture2D& getTexture(royale::CardType card) const;
	};
}