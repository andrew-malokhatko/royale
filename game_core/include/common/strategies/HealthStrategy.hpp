#pragma once

#include "GameObject.hpp"

namespace royale
{
	class HealthStrategy
	{
	public:
		//
		//	updates the object's health (optional, used for self destructing objects)
		//
		virtual void update(GameObject& gameObject) = 0;
	};
}