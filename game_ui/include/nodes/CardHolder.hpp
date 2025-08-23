#pragma once

#include "Card.hpp"
#include "game.hpp"
#include <vector>

namespace ui
{
	class CardHolder : public Node
	{	
		std::vector<Card> mCards;
		Card mNextCard;
		NodeId selectedCard = -1;

	public:
		CardHolder(Rectangle rec, const royale::Game& game);

		void draw() const override;
		void resize(int width, int height) override;
	};
}