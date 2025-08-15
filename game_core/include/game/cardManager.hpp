#pragma once

#include <array>
#include "CardType.hpp"
#include "config.hpp"
//#include "CardData.hpp"

namespace royale
{
	/*
	*  Data structure to hold the cards
	*/
	class CardManager
	{
		// First Game::CARD_NUMBER cards are available to be played and can be retrieved with getHand()
		std::array<CardType, Config::DECK_SIZE> mDeck{};

	public:
		CardManager();

		const std::array<CardType, Config::HAND_SIZE> getHand() const;
		CardType getNextCard() const;
		void drawCard(CardType card);
	};
}