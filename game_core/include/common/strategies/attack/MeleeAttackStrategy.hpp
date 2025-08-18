#pragma once

#include "AttackStrategy.hpp"

namespace royale
{
	class MeleeAttackStrategy : public AttackStrategy
	{
	public:
		void attack(GameObject& gameObject, AttackComponent& comp) override;
	};
}