#pragma once

#include "MovementStrategy.hpp"

namespace royale
{
	class GroundMovementStrategy : public MovementStrategy
	{
	public:
		void move(GameObject& gameObject, MovementComponent& comp) override;
	};
}