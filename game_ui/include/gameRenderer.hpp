#pragma once

#include <unordered_map>
#include "raylib.h"
#include "game.hpp"
#include "EntityType.hpp"


class GameRenderer
{
	const Color BACKGROUND_COLOR = WHITE;
	const Color TowerColor = LIGHTGRAY;

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
	GameRenderer();
	~GameRenderer();

	void render(const royale::Game& game, RenderTexture2D& target);
};