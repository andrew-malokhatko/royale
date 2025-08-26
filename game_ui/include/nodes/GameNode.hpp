#pragma once

#include <unordered_map>
#include "raylib.h"
#include "game.hpp"
#include "EntityType.hpp"
#include "EntityTextureManager.hpp"
#include "Node.hpp"

namespace ui
{
	class GameNode : public Node
	{
		EntityTextureManager mTextureManager{};
		const royale::Game& mGame;

		// MAINLY FOR DEBUG
		const std::unordered_map<royale::EntityType, Color> entityColors =
		{
			{royale::EntityType::None, BLACK},
			{royale::EntityType::Archer, PINK},
			{royale::EntityType::Goblin, BLUE},
			{royale::EntityType::Giant, PURPLE},
			{royale::EntityType::Prince, GOLD},
			{royale::EntityType::Bomber, RED},
			{royale::EntityType::Knight, BLUE},
			{royale::EntityType::Golem, RED},
			{royale::EntityType::Princess, ORANGE},
			{royale::EntityType::Arrows, SKYBLUE},
			{royale::EntityType::XBow, YELLOW}
		};

	public:
		GameNode(Rectangle rectangle, const royale::Game& game);

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;
	};
}