#pragma once

#include "vector2.hpp"

namespace royale
{
	class Config
	{
	public:
		static constexpr int CARD_NUMBER = 4;
		static constexpr int DECK_SIZE = 8;

		static constexpr  int FIELD_WIDTH = 18;
		static constexpr int FIELD_HEIGHT = 30;

		static constexpr double GAME_SPEED = 1.0;
		static constexpr double MAX_ELIXIR = 10.0;
		static constexpr double ELIXIR_GENERATION_SPEED = 0.5;

		static constexpr int TOWER_COUNT = 6;

		inline static const Vector2 ARCHER_TOWER_SIZE = { 3, 3 };
		inline static const Vector2 KING_TOWER_SIZE = { 4, 4 };
		inline static const Vector2 LEFT_TOWER_POSITION = {2, 4};
		inline static const Vector2 RIGHT_TOWER_POSITION = {FIELD_WIDTH - LEFT_TOWER_POSITION.x - ARCHER_TOWER_SIZE.x , LEFT_TOWER_POSITION.y};
		inline static const Vector2 KING_TOWER_POSITION = {FIELD_WIDTH / 2 - KING_TOWER_SIZE.x / 2, 1};
	};
}