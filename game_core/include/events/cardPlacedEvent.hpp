#pragma once

#include "event.hpp"
#include "vector2.hpp"
#include "CardType.hpp"


namespace royale
{
	class CardPlacedEvent : public Event
	{
		Vector2 mPosition;
		CardType mCard;

	public:
		CardPlacedEvent(Vector2 position, CardType card);
		void apply(Game& game) override;
		std::unique_ptr<Net::Packet> getPacket() const override;

		Vector2 getPosition() const;
		CardType getCard() const;
	};
}