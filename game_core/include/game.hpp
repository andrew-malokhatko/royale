#pragma once

#include <array>
#include <vector>
#include "vector2.hpp"
#include "Entity.hpp"
#include "event.hpp"
#include "cardManager.hpp"
#include "elixirManager.hpp"
#include "TowerManager.hpp"
#include "config.hpp"

namespace royale
{
	class Game
	{
	private:

		std::vector<Entity*> mEntities{};

		CardManager mCardManager{};
		ElixirManager mElixirManager{};
		TowerManager mTowerManager{};

	public:
		Game();
		~Game();
		
		void processEvents(const std::vector<std::unique_ptr<Event>>& events);
		void update(double dt);

		void placeCard(CardType card, Vector2 position);

		const std::vector<Entity*>& getEntities() const;
		const std::vector<Tower>& getTowers() const;

		const std::array<CardType, Config::HAND_SIZE> getCards() const;
		double getElixir() const;
		Vector2 getFieldSize() const;
	};
}