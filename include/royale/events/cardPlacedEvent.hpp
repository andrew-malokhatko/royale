#pragma once

#include "event.hpp"
#include "vector2.hpp"
#include "unitType.hpp"


namespace royale
{
	class CardPlacedEvent : public Event
	{
		Vector2 mPosition;
		UnitType mUnitType;

	public:
		CardPlacedEvent(Vector2 position, UnitType unit);
		void apply(Game& game);
	};
}