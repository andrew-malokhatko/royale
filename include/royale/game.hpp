#pragma once

#include <array>
#include <vector>
#include "vector2.hpp"
#include "unit.hpp"
#include "event.hpp"
#include "cardManager.hpp"
#include "elixirManager.hpp"
#include "towerManager.hpp"
#include "config.hpp"

namespace royale
{
	class Game
	{
	private:
		std::vector<Unit*> units{};
		CardManager mCardManager{};
		ElixirManager mElixirManager{};
		TowerManager mTowerManager{};
		// UnitManager
		// Maybe more
		//


	public:
		Game();
		~Game() = default;
		
		void processEvents(std::vector<Event*>& events);
		void update(double dt);

		void placeUnit(Unit* unit);

		const std::vector<Unit*>& getUnits() const;
		const std::array<UnitType, Config::CARD_NUMBER>& getCards() const;
		const std::array<Tower, Config::TOWER_COUNT>& getTowers() const;
		double getElixir() const;

		Vector2 getFieldSize() const;
	};
}