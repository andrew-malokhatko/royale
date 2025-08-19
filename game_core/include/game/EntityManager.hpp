#pragma once

#include "GameContext.hpp"
#include "Entity.hpp"
#include <unordered_map>

namespace royale
{
	class EntityManager
	{
		std::unordered_map<GameObjectId, Entity> mEntities{};

	public:
		EntityManager() = default;

		const std::unordered_map<GameObjectId, Entity>& getEntities() const;
		std::unordered_map<GameObjectId, Entity>& getEntities();

		void placeEntity(EntityType entityType, Vector2 position, GameContext& context);
		void removeEntity(GameObjectId id);

		const Entity* getEntityById(GameObjectId id) const;
		Entity* getEntityById(GameObjectId id);
		
		void update();
	};
}