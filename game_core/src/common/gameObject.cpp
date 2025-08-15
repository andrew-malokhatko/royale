#pragma once

#include "gameObject.hpp"
#include "game.hpp"

namespace royale
{
	GameObject::GameObject(Vector2 position, Vector2 size, Game& context) :
		mPosition {position},
		mSize {size},
		mContext{context}
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

	void GameObject::update()
	{
		for (auto& component : mComponents)
		{
			component->update(*this);
		}
	}

	Game& GameObject::getContext()
	{
		return mContext;
	}
}