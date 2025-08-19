#pragma once

#include "GameObject.hpp"
#include "game.hpp"

namespace royale
{
	GameObject::GameObject(Vector2 position, Vector2 size, GameContext& context) :
		mPosition{ position },
		mSize{ size },
		mContext{ context },
		ID{ ++IdGenerator }
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

	void GameObject::setPosition(const Vector2& position)
	{
		mPosition.x = position.x;
		mPosition.y = position.y;
	}

	void GameObject::setSize(const Vector2& size)
	{
		mSize.x = size.x;
		mSize.y = size.y;
	}

	GameObjectId GameObject::getId() const
	{
		return ID;
	}

	Vector2 GameObject::getCenter() const
	{
		return Vector2{
			mPosition.x + mSize.x / 2,
			mPosition.y + mSize.y / 2,
		};
	}

	bool GameObject::collides(Vector2 point) const
	{
		return mPosition.x < point.x && (mPosition.x + mSize.x) > point.x
			&& mPosition.y < point.y && (mPosition.y + mSize.y) > point.y;
	}

	bool GameObject::collides(const GameObject& other) const
	{
		return mPosition.x < other.mPosition.x + other.mSize.x &&
			other.mPosition.x < mPosition.x + mSize.x &&
			mPosition.y < other.mPosition.y + other.mSize.y &&
			other.mPosition.y < mPosition.y + mSize.y;
	}

	double GameObject::getDistance(Vector2 point) const
	{
		Vector2 center = getCenter();
		double xDif = std::abs(center.x - point.x);
		double yDif = std::abs(center.y - point.y);

		double hyp = std::sqrt(xDif * xDif + yDif * yDif);

		return hyp;
	}

	double GameObject::getDistance(const GameObject& other) const
	{
		return getDistance(other.getCenter());
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

	GameObject::GameObject(GameObject&& other) noexcept
		:
		mContext{ other.mContext },
		mPosition{ std::move(other.mPosition) },
		mSize{ std::move(other.mSize) },
		ID{ std::move(other.ID) },
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