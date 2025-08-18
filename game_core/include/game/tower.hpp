#pragma once

#include "GameObject.hpp"

namespace royale
{
	class Tower : public GameObject
	{
		bool mEnabled = true;
		bool mDestroyed = false;

		// Fire rate in seconds
		double mFireRate{};
		int mDamage{};

	public:
		Tower() = default;
		Tower(const Vector2& position, const Vector2& size, double fireRate, int damage, GameContext& context);
		Tower(Tower&& other) noexcept;

		Tower& operator=(Tower&& other) noexcept;
	};
}