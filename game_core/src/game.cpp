#include "game.hpp"
#include "Card.hpp"
#include "CardData.hpp"
#include "EntityData.hpp"
#include <iostream>

namespace royale
{
	Game::Game()
	{
		mElixirManager.startGenerating();
	}

	Game::~Game()
	{
		for (auto entity : mEntities)
		{
			delete entity;
		}

		mEntities.clear();
	}

	void Game::processEvents(const std::vector<std::unique_ptr<Event>>& events)
	{
		for (auto& event : events)
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

	void Game::placeCard(CardType cardType, Vector2 position)
	{
		//Vector2 position = unit->getPosition();

		const Card& card = CARD_DATA.at(cardType);

		for (const EntitySpawnInfo& spawnInfo : card.getEntitySpawnInfo())
		{
			Vector2 entityPos = {
				position.x + spawnInfo.offset.x,
				position.y + spawnInfo.offset.y,
			};

			Entity* entity = new Entity(spawnInfo.type, entityPos, *this);
			mEntities.push_back(entity);
		}

		std::cout << "Placed unit at: " << position.x << " - " << position.y << "\n";
	}

	const std::vector<Entity*>& Game::getEntities() const
	{
		return mEntities;
	}

	const std::array<CardType, Config::HAND_SIZE> Game::getCards() const
	{
		return mCardManager.getHand();
	}

	//const std::array<Tower, Config::TOWER_COUNT>& Game::getTowers() const
	//{
	//	return mTowerManager.getTowers();
	//}

	double Game::getElixir() const
	{
		return mElixirManager.getElixir();
	}

	Vector2 Game::getFieldSize() const
	{
		return Vector2{ static_cast<double>(Config::FIELD_WIDTH), static_cast<double>(Config::FIELD_HEIGHT) };
	}
}
