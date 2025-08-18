#include "attack/MeleeAttackStrategy.hpp"
#include "AttackComponent.hpp"
#include "GameContext.hpp"

namespace royale
{
	void MeleeAttackStrategy::attack(GameObject& gameObject, AttackComponent& comp)
	{
		auto& context = gameObject.getContext();
		auto& towers = context.getTowers();

		comp.mTarget = nullptr;
		double minDistance = DBL_MAX;

		for (auto& tower : towers)
		{
			double distance = gameObject.getDistance(tower);

			if (distance < minDistance)
			{
				minDistance = distance;
				comp.mTarget = &tower;
			}
		}
	}
}