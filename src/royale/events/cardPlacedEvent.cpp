#include "cardPlacedEvent.hpp"
#include "game.hpp"
#include "unit.hpp"

namespace royale
{

	CardPlacedEvent::CardPlacedEvent(Vector2 position, UnitType unitType)
		: Event(CardPlaced),
		mPosition{position},
		mUnitType{unitType}
	{
	}

	void CardPlacedEvent::apply(Game& game)
	{
		Vector2 defaultUnitSize = Vector2{ 50, 50 };

		// TODO:
		// initialize new unit
		Unit* knight = new Unit(mPosition, defaultUnitSize, mUnitType, 100);

		game.placeUnit(knight);
	}
};
