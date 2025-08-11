#pragma once

#include <array>
#include "card.hpp"
#include "config.hpp"

namespace royale
{
	/*
	*  Data structure to hold the cards
	*/
	class CardManager
	{
		// First Game::CARD_NUMBER cards are available to be played and can be retrieved with getHand()
		std::array<Card, Config::DECK_SIZE> mDeck {};

	public:
		CardManager();

		const std::array<Card, Config::HAND_SIZE > getHand() const;
		Card getNextCard() const;
		void drawCard(Card card);
	};
}