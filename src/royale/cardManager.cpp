#include "cardManager.hpp"
#include <cassert>

namespace royale
{
	// TEMP 
	CardManager::CardManager()
	{
		for (int i = 0; i < Config::DECK_SIZE; i++)
		{
			mDeck[i] = static_cast<UnitType>(i + 1);
		}
	}

	const std::array<UnitType, Config::CARD_NUMBER>& CardManager::getHand() const
	{
		assert(Config::CARD_NUMBER <= Config::DECK_SIZE);

		std::array<UnitType, Config::CARD_NUMBER> hand {};
		std::memcpy(hand.data(), mDeck.data(), hand.size() * sizeof(UnitType));
		return hand;
	}

	UnitType CardManager::getNextCard() const
	{
		assert(Config::CARD_NUMBER <= Config::DECK_SIZE);

		if (Config::CARD_NUMBER == Config::DECK_SIZE)
		{
			return None;
		}

		return mDeck[Config::CARD_NUMBER];
	}

	void CardManager::drawCard(UnitType unit)
	{
		assert(std::find(mDeck.begin(), mDeck.begin() + Config::CARD_NUMBER, unit) != mDeck.end());

		for (int i = 0; i < Config::CARD_NUMBER; i++)
		{
			if (mDeck[i] == unit)
			{
				mDeck[i] = mDeck[Config::CARD_NUMBER];
			}
		}

		// Move the deck 1 left
		for (int i = Config::DECK_SIZE - 1; i >= Config::CARD_NUMBER; i--)
		{
			mDeck[i - 1] = mDeck[i];
		}

		// Move drawn unit to the back
		mDeck[Config::DECK_SIZE - 1] = unit;
	}
}