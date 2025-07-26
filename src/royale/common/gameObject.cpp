#pragma once

#include "gameObject.hpp"

namespace royale
{
	GameObject::GameObject(Vector2 position, Vector2 size) :
		mPosition {position},
		mSize {size}
	{
	}

	const Vector2& GameObject::getPosition()
	{
		return mPosition;
	}

	const Vector2& GameObject::getSize()
	{
		return mSize;
	}

	bool GameObject::collides(Vector2 point)
	{
		return mPosition.x < point.x && (mPosition.x + mSize.x) > point.x
			&& mPosition.y < point.y && (mPosition.y + mSize.y) > point.y;
	}

	bool GameObject::collides(GameObject other)
	{
		return mPosition.x < other.mPosition.x + other.mSize.x &&
			other.mPosition.x < mPosition.x + mSize.x &&
			mPosition.y < other.mPosition.y + other.mSize.y &&
			other.mPosition.y < mPosition.y + mSize.y;
	}
}