#include "tower.hpp"

namespace royale
{
	Tower::Tower(const Vector2& position, const Vector2& size, double fireRate, int damage) :
		GameObject(position, size),
		mFireRate{ fireRate },
		mDamage{ damage }
	{
	}
}