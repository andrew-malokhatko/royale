#pragma once

#include "GameObject.hpp"

namespace royale
{
	// forward decl
	class MovementComponent;

	class MovementStrategy
	{
	public:
		//
		//	Algorithm that updates object's position
		//
		virtual void move(GameObject& gameObject, MovementComponent& comp) = 0;
	};
}