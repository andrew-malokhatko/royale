#pragma once

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
	};
}