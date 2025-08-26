#pragma once

#include <array>
#include <vector>
#include <ranges>
#include "vector2.hpp"

#include "event.hpp"
#include "cardManager.hpp"
#include "elixirManager.hpp"
#include "TowerManager.hpp"
#include "EntityManager.hpp"


namespace royale
{
	class Game : public GameContext
	{
	private:
		CardManager mCardManager{};
		ElixirManager mElixirManager{};
		TowerManager mTowerManager{};
		EntityManager mEntityManager{};

		double mDeltaTime{};

		std::vector<GameObject*> mToBeDeleted{};

	public:
		Game();

		const std::unordered_map<GameObjectId, Tower>& getTowers() const override;
		std::unordered_map<GameObjectId, Tower>& getTowers() override;

		const std::unordered_map<GameObjectId, Entity>& getEntities() const override;
		std::unordered_map<GameObjectId, Entity>& getEntities() override;

		//	Game Model
		void processEvents(const std::vector<std::unique_ptr<Event>>& events);
		void update(double dt);
		void placeCard(CardType card, Vector2 position);
		const std::array<CardType, Config::HAND_SIZE> getCards() const;
		const CardType getNextCard() const;
		Vector2 getFieldSize() const;


		// Game context
		double getDeltaTime() const override;
		double getElixir() const override;
		void spendElixir(double elixir) override;
		void removeEntity(GameObjectId id) override;
		void placeEntity(EntityType entityType, Vector2 position, GameContext& context) override;
	};
}