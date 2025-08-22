#include "cardManager.hpp"
//#include "CardData.hpp"
#include <cassert>

namespace royale
{
	// TEMPORARY
	// DECK SHOULD AT LEAST BE FILLED RANDOLY
	// !!!!!!!!!!
	CardManager::CardManager()
	{
		assert(Config::DECK_SIZE <= static_cast<size_t>(CardType::COUNT));

		for (size_t i = 0; i < Config::DECK_SIZE; ++i)
		{
			mDeck[i] = static_cast<CardType>(i + 1);
		}
	}

	const std::array<CardType, Config::HAND_SIZE> CardManager::getHand() const
	{
		assert(Config::HAND_SIZE <= Config::DECK_SIZE);

		std::array<CardType, Config::HAND_SIZE> hand = {};
		std::memcpy(hand.data(), mDeck.data(), hand.size() * sizeof(CardType));
		return hand;
	}

	CardType CardManager::getNextCard() const
	{
		assert(Config::HAND_SIZE<= Config::DECK_SIZE);

		if (Config::HAND_SIZE == Config::DECK_SIZE)
		{
			return CardType::None;
		}

		return mDeck[Config::HAND_SIZE];
	}

	void CardManager::drawCard(CardType card)
	{
		auto it = std::find(mDeck.begin(), mDeck.begin() + Config::HAND_SIZE, card);
		assert(it != mDeck.begin() + Config::HAND_SIZE);

		*it = mDeck[Config::HAND_SIZE];

		// Move the deck 1 left
		for (int i = Config::HAND_SIZE; i < Config::DECK_SIZE - 1; ++i)
		{
			mDeck[i] = mDeck[i + 1];
		}

		//// Move drawn unit to the back
		mDeck[Config::DECK_SIZE - 1] = card;
	}
}