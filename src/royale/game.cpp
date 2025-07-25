#include "game.hpp"
#include <iostream>

namespace royale
{
	Game::Game()
	{
		mElixirManager.startGenerating();
	}

	void Game::processEvents(std::vector<Event*>& events)
	{
		for (Event* event : events)
		{
			event->apply(*this);
		}
	}

	// expects dt in seconds 
	void Game::update(double dt)
	{
		dt = dt * Config::GAME_SPEED;
		
		mElixirManager.generateElixir(dt);
	}

	void Game::placeUnit(Unit* unit)
	{
		Vector2 position = unit->getPosition();

		std::cout << "Placed unit at: " << position.x << " - " << position.y << "\n";

		units.push_back(unit);
	}

	const std::vector<Unit*>& Game::getUnits() const
	{
		return units;
	}

	const std::array<UnitType, 4>& Game::getCards() const
	{
		return mCardManager.getHand();
	}

	const std::array<Tower, Config::TOWER_COUNT>& Game::getTowers() const
	{
		return mTowerManager.getTowers();
	}

	double Game::getElixir() const
	{
		return mElixirManager.getElixir();
	}

	Vector2 Game::getFieldSize() const
	{
		return Vector2{ static_cast<double>(Config::FIELD_WIDTH), static_cast<double>(Config::FIELD_HEIGHT) };
	}
}
