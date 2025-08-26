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
		Card* selectedCard = nullptr;
		Vector2 selectedCardPos{};

	public:
		CardHolder(Rectangle rec, const royale::Game& game);

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;
		void updateSelf() override;

		void handleClick(MouseClickEvent mouseClick) override;
		void handleMove(MouseMoveEvent mouseMove) override;
	};
}