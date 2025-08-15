#pragma once

#include "GameObject.hpp"

namespace royale
{
	class AttackStrategy
	{
	public:
		//
		//	Algorithm that attacks on behalf of the object
		//
		virtual void attack(GameObject& gameObject) = 0;
	};
}