#include "cardPlacedEvent.hpp"
#include "game.hpp"
#include "unit.hpp"

namespace royale
{
	CardPlacedEvent::CardPlacedEvent(Vector2 position, Card card)
		: Event(CardPlaced),
		mPosition{position},
		mCard{card}
	{
	}

	void CardPlacedEvent::apply(Game& game)
	{
		Unit* knight = new Unit(mCard, mPosition);

		game.placeUnit(knight);
	}
};
