#pragma once

#include "GameObject.hpp"
#include "EntityType.hpp"

namespace royale
{
	class Tower : public GameObject
	{
		bool mEnabled = true;
		bool mDestroyed = false;

	public:
		Tower() = default;
		Tower(EntityType type, const Vector2& position, const Vector2& size, GameContext& context);
		Tower(Tower&& other) noexcept;

		Tower& operator=(Tower&& other) noexcept;
	};
}