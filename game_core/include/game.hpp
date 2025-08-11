#pragma once

#include <array>
#include <vector>
#include "vector2.hpp"
#include "unit.hpp"
#include "spell.hpp"
#include "structure.hpp"
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
		std::vector<Spell*> spell{};
		std::vector<Structure*> structure{};

		CardManager mCardManager{};
		ElixirManager mElixirManager{};
		TowerManager mTowerManager{};
		// UnitManager
		// SpellManager ???
		// Maybe more
		//


	public:
		Game();
		~Game() = default;
		
		void processEvents(const std::vector<std::unique_ptr<Event>>& events);
		void update(double dt);

		void placeUnit(Unit* unit);

		const std::vector<Unit*>& getUnits() const;
		// std::vector<Spell*>& getSpells() const;
		// const std::vector<Structure*>& getStructures() const;

		const std::array<Card, Config::HAND_SIZE> getCards() const;
		const std::array<Tower, Config::TOWER_COUNT>& getTowers() const;
		double getElixir() const;

		Vector2 getFieldSize() const;
	};
}