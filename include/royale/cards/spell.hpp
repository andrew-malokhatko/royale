#pragma once

#include "card.hpp"

namespace royale
{
	class Spell : public GameObject
	{
		Card mCard{};

		// add lifetime etc

		static Vector2 getSpellSize(Card card)
		{
			return spellStats[toIndex(card)].size;
		}

	public:
		Spell(Card card, Vector2 position)
			: GameObject(position, getSpellSize(card)),
			mCard{ card }
		{
		}

		Card getCard()
		{
			return mCard;
		}
	};
}