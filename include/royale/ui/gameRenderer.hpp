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
		const std::unordered_map<Card, Color> unitColors = 
		{
			{Card::Arrows, WHITE},
			{Card::Knight, BLUE},
			{Card::Bomber, RED},
			{Card::Prince, GOLD},
			{Card::Goblins, GREEN},
			{Card::Giant, PURPLE},
		};

	public:
		GameRenderer();
		~GameRenderer();

		void render(const Game& game, RenderTexture2D& target);
	};
}