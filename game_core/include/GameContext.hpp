#pragma once

#include <unordered_map>
#include "Tower.hpp"
#include "vector2.hpp"
#include "Entity.hpp"

namespace royale
{
	class GameContext
	{

	public:

		virtual const std::unordered_map<GameObjectId, Tower>& getTowers() const = 0;
		virtual std::unordered_map<GameObjectId, Tower>& getTowers() = 0;

		virtual const std::unordered_map<GameObjectId, Entity>& getEntities() const = 0;
		virtual std::unordered_map<GameObjectId, Entity>& getEntities() = 0;
		
		//	Entity API 
		virtual void placeEntity(EntityType entityType, Vector2 position, GameContext& context) = 0;
		virtual void removeEntity(GameObjectId id) = 0;

		// Elixir API
		virtual double getElixir() const = 0;
		virtual void spendElixir(double elixir) = 0;

		// Game API
		virtual double getDeltaTime() const = 0;
	};
}