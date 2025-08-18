#pragma once

#include "GameObject.hpp"

namespace royale
{
	// forward decl
	class AttackComponent;

	class AttackStrategy
	{
	public:
		//
		//	Algorithm that attacks on behalf of the object
		//
		virtual void attack(GameObject& gameObject, AttackComponent& comp) = 0;
	};
}