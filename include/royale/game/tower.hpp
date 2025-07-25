#pragma once

#include "unit.hpp"

namespace royale
{
	class Tower
	{
		Vector2 mPosition{};
		Vector2 mSize{};

		bool mEnabled = true;
		bool mBroken = false;

		// Fire rate in seconds
		double mFireRate{};
		int mDamage{};

	public:
		Tower() = default;
		Tower(const Vector2& position, const Vector2& size, double fireRate, int damage);
		Vector2 getPosition();
		Vector2 getSize();
		//void update(double dt);
		//void shoot(Unit* unit);
	};
}