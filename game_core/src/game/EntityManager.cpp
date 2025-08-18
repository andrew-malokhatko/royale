#pragma once

#include "EntityManager.hpp"
#include <algorithm>

namespace royale
{
	EntityManager::~EntityManager()
	{
		for (Entity* entity : mEntities)
		{
			delete entity;
		}
		mEntities.clear();
	}

	const std::vector<Entity*>& EntityManager::getEntities() const
	{
		return mEntities;
	}

	void EntityManager::placeEntity(EntityType entityType, Vector2 position, GameContext& context)
	{
		Entity* entity = new Entity(entityType, position, context);
		mEntities.push_back(entity);
	}

	void EntityManager::removeEntity(Entity* entity)
	{
		auto it = std::find(mEntities.begin(), mEntities.end(), entity);
		if (it != mEntities.end())
		{
			mEntities.erase(it);
		}
	}

	void EntityManager::update()
	{
		for (Entity* entity : mEntities)
		{
			entity->update();
		}
	}
}