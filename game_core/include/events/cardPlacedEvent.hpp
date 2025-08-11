#pragma once

#include "event.hpp"
#include "vector2.hpp"
#include "card.hpp"


namespace royale
{
	class CardPlacedEvent : public Event
	{
		Vector2 mPosition;
		Card mCard;

	public:
		CardPlacedEvent(Vector2 position, Card card);
		void apply(Game& game) override;
		std::unique_ptr<Net::Packet> getPacket() const override;

		Vector2 getPosition() const;
		Card getCard() const;
	};
}