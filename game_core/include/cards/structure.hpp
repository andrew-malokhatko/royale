#pragma once

#include "card.hpp"

namespace royale
{
	class Structure : public GameObject
	{
		Card mCard{};

		// add lifetime etc

		static Vector2 getStructureSize(Card card)
		{
			return unitStats[toIndex(card)].size;
		}

	public:
		Structure(Card card, Vector2 position)
			: GameObject(position, getStructureSize(card)),
			mCard{ card }
		{
		}

		Card getCard()
		{
			return mCard;
		}
	};
}