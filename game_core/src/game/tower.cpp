#include "tower.hpp"

namespace royale
{
	Tower::Tower(const Vector2& position, const Vector2& size, double fireRate, int damage, Game& context)
		:
		GameObject(position, size, context),
		mFireRate{fireRate},
		mDamage {damage}
	{
	}

	Tower::Tower(Tower&& other) noexcept
		:
		GameObject(std::move(other)),
		mEnabled(other.mEnabled),
		mDestroyed(other.mDestroyed),
		mFireRate(other.mFireRate),
		mDamage(other.mDamage)
	{
	}

	Tower& Tower::operator=(Tower&& other) noexcept
	{
		if (this != &other)
		{
			// Assign base part
			GameObject::operator=(std::move(other));

			mEnabled = other.mEnabled;
			mDestroyed = other.mDestroyed;
			mFireRate = other.mFireRate;
			mDamage = other.mDamage;
		}
		return *this;
	}
}