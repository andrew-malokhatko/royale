#include "tower.hpp"

namespace royale
{
	Tower::Tower(const Vector2& position, const Vector2& size, double fireRate, int damage)
	{
		mPosition = position;
		mSize = size;
		mFireRate = fireRate;
		mDamage = damage;
	}

	Vector2 Tower::getPosition()
	{
		return mPosition;
	}

	Vector2 Tower::getSize()
	{
		return mSize;
	}
}