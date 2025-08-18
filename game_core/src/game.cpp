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
		mTowerManager.placeTowers(*this);
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
		mDeltaTime = dt * Config::GAME_SPEED;
		
		mEntityManager.update();
		//mTowerManager.udpate();

		mElixirManager.generateElixir(dt);
	}

	void Game::placeCard(CardType cardType, Vector2 position)
	{
		const Card& card = CARD_DATA.at(cardType);
		
		if (card.getCost() > mElixirManager.getElixir())
		{
			return;
		}
		mElixirManager.spendElixir(card.getCost());

		for (const EntitySpawnInfo& spawnInfo : card.getEntitySpawnInfo())
		{
			Vector2 entityPos = {
				position.x + spawnInfo.offset.x,
				position.y + spawnInfo.offset.y,
			};

			mEntityManager.placeEntity(spawnInfo.type, entityPos, *this);
		}

		std::cout << "Placed unit at: " << position.x << " - " << position.y << "\n";
	}

	const std::vector<Entity*>& Game::getEntities() const
	{
		return mEntityManager.getEntities();
	}

	const std::vector<Tower>& Game::getTowers() const
	{
		return mTowerManager.getTowers();
	}

	double Game::getDeltaTime() const
	{
		return mDeltaTime;
	}

	const std::array<CardType, Config::HAND_SIZE> Game::getCards() const
	{
		return mCardManager.getHand();
	}

	double Game::getElixir() const
	{
		return mElixirManager.getElixir();
	}

	void Game::spendElixir(double elixir)
	{
		mElixirManager.spendElixir(elixir);
	}

	void Game::removeEntity(Entity* entity)
	{
		mEntityManager.removeEntity(entity);
	}

	void Game::placeEntity(EntityType entityType, Vector2 position, GameContext& context)
	{
		mEntityManager.placeEntity(entityType, position, context);
	}

	Vector2 Game::getFieldSize() const
	{
		return Vector2{ static_cast<double>(Config::FIELD_WIDTH), static_cast<double>(Config::FIELD_HEIGHT) };
	}
}