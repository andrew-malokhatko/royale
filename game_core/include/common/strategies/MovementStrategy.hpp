#pragma once

#include "GameObject.hpp"

namespace royale
{
	class MovementStrategy
	{
		//
		//	Algorithm that updates object's position
		//
		virtual void move(GameObject& gameObject) = 0;
	};
}