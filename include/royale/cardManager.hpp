#pragma once

#include <array>
#include "unitType.hpp"
#include "config.hpp"

namespace royale
{
	/*
	*  Data structure to hold the cards
	*/
	class CardManager
	{
		// First Game::CARD_NUMBER cards are available to be played and can be retrieved with getHand()
		std::array<UnitType, Config::DECK_SIZE> mDeck {};

	public:
		CardManager();

		const std::array<UnitType, Config::CARD_NUMBER>& getHand() const;
		UnitType getNextCard() const;
		void drawCard(UnitType unit);
	};
}