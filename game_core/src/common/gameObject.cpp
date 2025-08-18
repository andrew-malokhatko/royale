#pragma once

#include "gameObject.hpp"
#include "game.hpp"

namespace royale
{
	GameObject::GameObject(Vector2 position, Vector2 size, GameContext& context) :
		mPosition{ position },
		mSize{ size },
		mContext{ context }
	{
	}

	const Vector2& GameObject::getPosition() const
	{
		return mPosition;
	}

	const Vector2& GameObject::getSize() const
	{
		return mSize;
	}

	bool GameObject::collides(Vector2 point) const
	{
		return mPosition.x < point.x && (mPosition.x + mSize.x) > point.x
			&& mPosition.y < point.y && (mPosition.y + mSize.y) > point.y;
	}

	bool GameObject::collides(GameObject other) const
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

	GameContext& GameObject::getContext()
	{
		return mContext;
	}

	GameObject::GameObject(GameObject&& other)
		:
		mContext{ other.mContext },
		mPosition{ std::move(other.mPosition) },
		mSize{ std::move(other.mSize) },
		mComponents {std::move(other.mComponents) }
	{
	}

	GameObject& GameObject::operator=(GameObject&& other) noexcept
	{
		if (this != &other)
		{
			mPosition = std::move(other.mPosition);
			mSize = std::move(other.mSize);
			mComponents = std::move(other.mComponents);
		}

		return *this;
	}
}