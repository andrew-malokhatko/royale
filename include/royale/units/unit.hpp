#pragma once

#include "unitType.hpp"
#include "gameObject.hpp"

namespace royale
{
	class Unit : public GameObject
	{
		UnitType mUnitType {};
		int mHealth {};

	public:
		Unit(Vector2 position, Vector2 size, UnitType unitType, int health)
			: GameObject(position, size),
			mUnitType {unitType},
			mHealth {health}
		{
		}

		UnitType getUnitType()
		{
			return mUnitType;
		}

		int getHealth()
		{
			return mHealth;
		}

	};
}