#include "health/BaseHealthStrategy.hpp"
#include "HealthComponent.hpp"
#include "GameContext.hpp"

namespace royale
{
	void BaseHealthStrategy::update(GameObject& gameObject, HealthComponent& comp)
	{
		if (comp.getHealth() <= 0)
		{
			auto& context = gameObject.getContext();
			context.removeEntity(gameObject.getId());
		}
	}
}