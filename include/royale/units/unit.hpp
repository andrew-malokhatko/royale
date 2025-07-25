#pragma once

#include "vector2.hpp"
#include "unitType.hpp"

namespace royale
{
	class Unit
	{
		Vector2 mPosition {};
		Vector2 mSize {};
		UnitType mUnitType {};
		int mHealth {};

	public:
		Unit() = delete;

		Unit(Vector2 position, Vector2 size, UnitType unitType, int health)
			: mPosition {position},
			mSize {size},
			mUnitType {unitType},
			mHealth {health}
		{
		}

		~Unit()
		{

		}

		Vector2 getPosition()
		{
			return mPosition;
		}

		Vector2 getSize()
		{
			return mSize;
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