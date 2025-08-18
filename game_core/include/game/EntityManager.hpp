#pragma once

#include "GameContext.hpp"
#include "Entity.hpp"
#include <vector>

namespace royale
{
	class EntityManager
	{
		std::vector<Entity*> mEntities{};

	public:

		EntityManager() = default;
		~EntityManager();

		const std::vector<Entity*>& getEntities() const;

		void placeEntity(EntityType entityType, Vector2 position, GameContext& context);
		void removeEntity(Entity* entity);

		void update();
	};
}