#pragma once

#include "unit.hpp"
#include "gameObject.hpp"

namespace royale
{
	class Tower : public GameObject
	{
		bool mEnabled = true;
		bool mBroken = false;

		// Fire rate in seconds
		double mFireRate{};
		int mDamage{};

	public:
		Tower() = default;
		Tower(const Vector2& position, const Vector2& size, double fireRate, int damage);
		//void update(double dt);
		//void shoot(Unit* unit);
	};
}