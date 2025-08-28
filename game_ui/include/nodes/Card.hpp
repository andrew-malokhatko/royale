#pragma once

#include "Node.hpp"
#include "colorScheme.hpp"
#include "CardType.hpp"


namespace ui
{
	class Card : public Node
	{
		royale::CardType mCard{};

		Texture2D mTexture{};

		bool mSelected{};
		bool mDragged{};

	private:
		void loadTexture();

	public:
		Card() = default;
		Card(royale::CardType card, Rectangle rectangle);
		~Card();

		void setCard(royale::CardType card);

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;

		void select();
		void deselect();

		void startDrag();
		void stopDrag();

		royale::CardType getCardType() const;
		bool isDragged() const;
		bool isSelected() const;
	};
}