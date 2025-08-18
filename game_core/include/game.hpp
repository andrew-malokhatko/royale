#pragma once

#include <array>
#include <vector>
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

	public:
		Game();

		const std::vector<Entity*>& getEntities() const override;
		std::vector<Tower>& getTowers() override;

		const std::vector<Tower>& getTowers() const;

		//	Game Model
		void processEvents(const std::vector<std::unique_ptr<Event>>& events);
		void update(double dt);
		void placeCard(CardType card, Vector2 position);
		const std::array<CardType, Config::HAND_SIZE> getCards() const;
		Vector2 getFieldSize() const;


		// Game context
		double getDeltaTime() const override;
		double getElixir() const override;
		void spendElixir(double elixir) override;
		void removeEntity(Entity* entity) override;
		void placeEntity(EntityType entityType, Vector2 position, GameContext& context) override;
	};
}