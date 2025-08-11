#include "cardPlacedEvent.hpp"
#include "CardPlacedPacket.hpp"
#include "game.hpp"
#include "unit.hpp"

namespace royale
{
	CardPlacedEvent::CardPlacedEvent(Vector2 position, Card card)
		: Event(EventType::CardPlaced),
		mPosition{position},
		mCard{card}
	{
	}

	void CardPlacedEvent::apply(Game& game)
	{
		Unit* knight = new Unit(mCard, mPosition);

		game.placeUnit(knight);
	}

	std::unique_ptr<Net::Packet> CardPlacedEvent::getPacket() const
	{
		return std::make_unique<Net::CardPlacedPacket>(*this);
	}

	Vector2 CardPlacedEvent::getPosition() const
	{
		return mPosition;
	}

	Card CardPlacedEvent::getCard() const
	{
		return mCard;
	}
};
