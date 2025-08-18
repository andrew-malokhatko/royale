#pragma once

#include "GameObject.hpp"

namespace royale
{
	// forward decl
	class HealthComponent;

	class HealthStrategy
	{
	public:
		//
		//	updates the object's health (optional, used for self destructing objects)
		//
		virtual void update(GameObject& gameObject, HealthComponent& comp) = 0;
	};
}