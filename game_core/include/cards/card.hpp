#pragma once

#include <cstdint>

namespace royale
{
	enum class Card : uint8_t
	{
		// Units
		None,
		Bomber,
		Knight,
		Giant,
		Goblins,
		Golem,
		Prince,
		Princess,

		// Spells
		Arrows,

		// Structures
		XBow,
	};
		
	enum class CardType : uint8_t
	{
		Unit,
		Spell,
		Structure,
	};

	static constexpr int toIndex(Card card)
	{
		return static_cast<int>(card);
	}

	static constexpr int toIndex(CardType cardType)
	{
		return static_cast<int>(cardType);
	}
	 

	static constexpr int CARD_COUNT = 10;
}