#pragma once

#include <unordered_map>
#include "raylib.h"
#include "game.hpp"

namespace royale
{
	class GameRenderer
	{
		const Color BACKGROUND_COLOR = WHITE;
		const Color TowerColor = LIGHTGRAY;
		const std::unordered_map<UnitType, Color> unitColors = 
		{
			{UnitType::Knight, BLUE},
			{UnitType::Bomber, RED},
			{UnitType::Prince, GOLD},
			{UnitType::Goblins, GREEN},
			{UnitType::Archers, PURPLE}
		};

	public:
		GameRenderer();
		~GameRenderer();

		void render(const Game& game, RenderTexture2D& target);
	};
}