#pragma once

#include "AttackStrategy.hpp"

namespace royale
{
	class ArrowAttackStrategy : public AttackStrategy
	{
	public:
		void attack(GameObject& gameObject, AttackComponent& comp) override;
	};
}