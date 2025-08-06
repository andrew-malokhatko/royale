#pragma once

#include "card.hpp"
#include "gameObject.hpp"
#include "cardStats.hpp"

namespace royale
{
	class Unit : public GameObject
	{
		Card mCard{};

		static Vector2 getUnitSize(Card card)
		{
			return unitStats[toIndex(card)].size;
		}

	public:
		Unit(Card card, Vector2 position)
			: GameObject(position, getUnitSize(card)),
			mCard { card }
		{
		}

		Card getCard()
		{
			return mCard;
		}
	};
}