#include "cardPlacedEvent.hpp"
#include "CardPlacedPacket.hpp"
#include "game.hpp"

namespace royale
{
	CardPlacedEvent::CardPlacedEvent(Vector2 position, CardType card)
		: Event(EventType::CardPlaced),
		mPosition{position},
		mCard{card}
	{
	}

	void CardPlacedEvent::apply(Game& game)
	{
		game.placeCard(mCard, mPosition);
	}

	std::unique_ptr<Net::Packet> CardPlacedEvent::getPacket() const
	{
		return std::make_unique<Net::CardPlacedPacket>(*this);
	}

	Vector2 CardPlacedEvent::getPosition() const
	{
		return mPosition;
	}

	CardType CardPlacedEvent::getCard() const
	{
		return mCard;
	}
};
