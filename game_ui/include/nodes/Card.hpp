#pragma once

#include <functional>
#include "Node.hpp"
#include "colorScheme.hpp"
#include "CardType.hpp"
#include "textureManager.hpp"

namespace ui
{
	class Card : public Node
	{
		royale::CardType mCard{};

		//std::function<void(Card&)> dropCallback;

		bool mSelected{};
		bool mDragged{};

	public:
		Card() = default;
		Card(royale::CardType card, Rectangle rectangle);

		void draw() const override;
		void resize(int width, int height) override;

		/*void update() override;
		void onClick() override;
		void onRelease() override;*/
	};
}