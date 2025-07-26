#pragma once

#include "vector2.hpp"

namespace royale
{
	class GameObject
	{
	protected:
		Vector2 mPosition;
		Vector2 mSize;

	public:
		GameObject() = default;
		GameObject(Vector2 position, Vector2 size);

		const Vector2& getPosition();
		const Vector2& getSize();

		bool collides(Vector2 point);
		bool collides(GameObject other);
	};
}