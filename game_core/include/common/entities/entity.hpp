#pragma once

#include "gameObject.hpp"
#include "EntityData.hpp"

namespace royale
{
	// forward decl
	class Game;

	class Entity : public GameObject
	{
		EntityType mEntityType;

	public:
		Entity(EntityType type, Vector2 position, Game& context)
			: GameObject{ position, Vector2{1, 1}, context },
			mEntityType { type }
		{
			const EntityData& data = ENTITY_DATA.at(mEntityType);

			// costruct the entity from precomputed componen ts
			for (const auto& component : data.components)
			{
				auto componentInstance = component->clone();
				addComponent(std::move(componentInstance));
			}
		}
		
		EntityType getType() const
		{
			return mEntityType;
		}
	};
}