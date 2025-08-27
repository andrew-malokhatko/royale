#pragma once

#include "ISelectedCard.hpp"
#include "game.hpp"
#include <vector>
#include <functional>

namespace ui
{
	class CardHolder : public Node, public ISelectedCard
	{	
		std::vector<Card> mCards;
		Card mNextCard;
		Card* selectedCard = nullptr;
		Vector2 selectedCardPos{};

		const royale::Game& mGame;
		std::function<bool(void)> onCardDropped;

	public:
		CardHolder(Rectangle rec, const royale::Game& game);
		 
		void drawSelf() const override;
		void resizeSelf(int width, int height) override;
		void updateSelf() override;

		void handleClick(MouseClickEvent mouseClick) override;
		void handleMove(MouseMoveEvent mouseMove) override;

		const Card* getSelectedCard() override;
		void hideSelectedCard() override;
		void showSelectedCard() override;

		void setCardDroppedCallback(std::function<bool(void)> dropCallback);
	};
}