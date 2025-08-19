#include "Tower.hpp"
#include "EntityData.hpp"


namespace royale
{
	Tower::Tower(EntityType type, const Vector2& position, const Vector2& size, GameContext& context)
		:
		GameObject(position, size, context)
	{
		const EntityData& data = ENTITY_DATA.at(type);

		// costruct the entity from preloaded components
		for (const auto& component : data.components)
		{
			auto componentInstance = component->clone();
			addComponent(std::move(componentInstance));
		}
	}

	Tower::Tower(Tower&& other) noexcept
		:
		GameObject(std::move(other)),
		mEnabled(other.mEnabled),
		mDestroyed(other.mDestroyed)
	{
	}

	Tower& Tower::operator=(Tower&& other) noexcept
	{
		if (this != &other)
		{
			// Assign base part
			GameObject::operator=(std::move(other));

			mEnabled = other.mEnabled;
			mDestroyed = other.mDestroyed;
		}
		return *this;
	}
}