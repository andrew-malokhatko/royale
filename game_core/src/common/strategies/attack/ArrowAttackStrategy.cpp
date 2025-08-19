#include "attack/ArrowAttackStrategy.hpp"
#include "GameContext.hpp"
#include "AttackComponent.hpp"
#include "HealthComponent.hpp"
#include <limits>

namespace royale
{
	void ArrowAttackStrategy::attack(GameObject& gameObject, AttackComponent& comp)
	{
		auto& context = gameObject.getContext();
		auto& towers = context.getTowers();
		
		comp.mTarget = nullptr;
		double minDistance = DBL_MAX;

		// find target
		for (auto& [id, tower] : towers)
		{
			double distance = gameObject.getDistance(tower);

			if (distance < minDistance)
			{
				minDistance = distance;
				comp.mTarget = &tower;
			}
		}

		if (comp.mTarget == nullptr)
		{
			return;
		}
		
		// attack
		comp.timeSinceLastAttack += context.getDeltaTime();
		if (comp.timeSinceLastAttack > (1.0 / comp.mSpeed))
		{
			auto& healthComp = comp.mTarget->getComponent<HealthComponent>();
			healthComp.takeDamage(comp.mDamage);
			comp.timeSinceLastAttack = 0.0;
		}
	}
}