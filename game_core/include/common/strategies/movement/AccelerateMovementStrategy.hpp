#pragma once

#include "MovementStrategy.hpp"

namespace royale
{
	class AccelerateMovementStrategy : public MovementStrategy
	{
	public:
		void move(GameObject& gameObject, MovementComponent& comp) override;
	};
}