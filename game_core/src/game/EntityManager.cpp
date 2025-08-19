#pragma once

#include "EntityManager.hpp"
#include <algorithm>

namespace royale
{
	const std::unordered_map<GameObjectId, Entity>& EntityManager::getEntities() const
	{
		return mEntities;
	}

	std::unordered_map<GameObjectId, Entity>& EntityManager::getEntities()
	{
		return mEntities;
	}

	void EntityManager::placeEntity(EntityType entityType, Vector2 position, GameContext& context)
	{
		Entity entity = Entity(entityType, position, context);
		mEntities.emplace(entity.getId(), std::move(entity));
	}

	void EntityManager::removeEntity(GameObjectId id)
	{
		mEntities.erase(id);
	}

	const Entity* EntityManager::getEntityById(GameObjectId id) const
	{
		if (mEntities.contains(id))
		{
			return &mEntities.at(id);
		}
		return nullptr;
	}

	Entity* EntityManager::getEntityById(GameObjectId id)
	{
		if (mEntities.contains(id))
		{
			return &mEntities.at(id);
		}
		return nullptr;
	}

	void EntityManager::update()
	{
		for (auto& [id, entity] : mEntities)
		{
			entity.update();
		}
	}
}