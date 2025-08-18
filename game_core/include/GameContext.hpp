#pragma once

#include <vector>
#include "Tower.hpp"
#include "vector2.hpp"
#include "Entity.hpp"

namespace royale
{
	class GameContext
	{

	public:

		// Tower API
		virtual std::vector<Tower>& getTowers() = 0;
		
		//	Entity API 
		virtual const std::vector<Entity*>& getEntities() const = 0;
		virtual void placeEntity(EntityType entityType, Vector2 position, GameContext& context) = 0;
		virtual void removeEntity(Entity* entity) = 0;

		// Elixir API
		virtual double getElixir() const = 0;
		virtual void spendElixir(double elixir) = 0;

		// Game API
		virtual double getDeltaTime() const = 0;
	};
}