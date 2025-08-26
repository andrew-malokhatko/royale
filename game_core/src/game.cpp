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
		mTowerManager.update();

		// delete objects that were scheduled for deletion
		for (auto* gameObject : mToBeDeleted)
		{
			GameObjectId id = gameObject->getId();

			// either of 1 function triggers
			mEntityManager.removeEntity(id);
			mTowerManager.removeTower(id);
		}
		mToBeDeleted.clear();

		mElixirManager.generateElixir(dt);
	}

	void Game::placeCard(CardType cardType, Vector2 position)
	{
		const Card& card = CARD_DATA.at(cardType);
		
		// UNCOMMENT AS NEEDED
		//if (card.getCost() > mElixirManager.getElixir())
		//{
		//	return;
		//}
		//mElixirManager.spendElixir(card.getCost());

		mCardManager.drawCard(cardType);

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

	const std::unordered_map<GameObjectId, Tower>& Game::getTowers() const
	{
		return mTowerManager.getTowers();
	}

	std::unordered_map<GameObjectId, Tower>& Game::getTowers()
	{
		return mTowerManager.getTowers();
	}

	const std::unordered_map<GameObjectId, Entity>& Game::getEntities() const
	{
		return mEntityManager.getEntities();
	}

	std::unordered_map<GameObjectId, Entity>& Game::getEntities()
	{
		return mEntityManager.getEntities();
	}

	double Game::getDeltaTime() const
	{
		return mDeltaTime;
	}

	const std::array<CardType, Config::HAND_SIZE> Game::getCards() const
	{
		return mCardManager.getHand();
	}

	const CardType Game:: getNextCard() const
	{
		return mCardManager.getNextCard();
	}

	double Game::getElixir() const
	{
		return mElixirManager.getElixir();
	}

	void Game::spendElixir(double elixir)
	{
		mElixirManager.spendElixir(elixir);
	}

	// schedule the deletion
	void Game::removeEntity(GameObjectId id)
	{
		auto* e = mEntityManager.getEntityById(id);
		auto* t = mTowerManager.getTowerById(id);

		assert(e == nullptr || t == nullptr);

		if (e)
		{
			mToBeDeleted.push_back(e);
		}
		else if (t)
		{
			mToBeDeleted.push_back(t);
		}
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