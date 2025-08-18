#pragma once

#include "HealthStrategy.hpp"

namespace royale
{
	class BaseHealthStrategy : public HealthStrategy
	{
	public:
		void update(GameObject& gameObject, HealthComponent& comp) override;
	};
}