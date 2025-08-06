#include "cardManager.hpp"
#include <cassert>

namespace royale
{
	// TEMPORARY
	// DECK SHOULD AT LEAST BE FILLED RANDOLY
	CardManager::CardManager()
	{
		for (int i = 0; i < Config::DECK_SIZE; i++)
		{
			mDeck[i] = static_cast<Card>(i + 1);
		}
	}

	const std::array<Card, Config::HAND_SIZE> CardManager::getHand() const
	{
		assert(Config::HAND_SIZE <= Config::DECK_SIZE);

		std::array<Card, Config::HAND_SIZE> hand {};
		std::memcpy(hand.data(), mDeck.data(), hand.size() * sizeof(Card));
		return hand;
	}

	Card CardManager::getNextCard() const
	{
		assert(Config::HAND_SIZE<= Config::DECK_SIZE);

		if (Config::HAND_SIZE == Config::DECK_SIZE)
		{
			return Card::None;
		}

		return mDeck[Config::HAND_SIZE];
	}

	void CardManager::drawCard(Card card)
	{
		assert(std::find(mDeck.begin(), mDeck.begin() + Config::HAND_SIZE, card) != mDeck.end());

		for (int i = 0; i < Config::HAND_SIZE; i++)
		{
			if (mDeck[i] == card)
			{
				mDeck[i] = mDeck[Config::HAND_SIZE];
			}
		}

		// Move the deck 1 left
		for (int i = Config::DECK_SIZE - 1; i >= Config::HAND_SIZE; i--)
		{
			mDeck[i - 1] = mDeck[i];
		}

		// Move drawn unit to the back
		mDeck[Config::DECK_SIZE - 1] = card;
	}
}