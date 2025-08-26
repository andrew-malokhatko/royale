#pragma once

#include <functional>
#include "Node.hpp"
#include "colorScheme.hpp"
#include "CardType.hpp"


namespace ui
{
	class Card : public Node
	{
		royale::CardType mCard{};

		Texture2D mTexture{};

		//std::function<void(Card&)> dropCallback;

		bool mSelected{};
		bool mDragged{};

	private:
		void loadTexture();

	public:
		Card() = default;
		Card(royale::CardType card, Rectangle rectangle);
		~Card();

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;

		/*void update() override;
		void onClick() override;
		void onRelease() override;*/
	};
}