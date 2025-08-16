#pragma once

#include "gameObject.hpp"

namespace royale
{
	// forward decl for a Game class
	class Game;

	class Tower : public GameObject
	{
		bool mEnabled = true;
		bool mDestroyed = false;

		// Fire rate in seconds
		double mFireRate{};
		int mDamage{};

	public:
		Tower() = default;
		Tower(const Vector2& position, const Vector2& size, double fireRate, int damage, Game& context);

		// Moves
		Tower(Tower&& other) noexcept;
		Tower& operator=(Tower&& other) noexcept;

		//void update(double dt);
		//void shoot(Unit* unit);
	};
}