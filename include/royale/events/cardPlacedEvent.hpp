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
		void apply(Game& game);
	};
}