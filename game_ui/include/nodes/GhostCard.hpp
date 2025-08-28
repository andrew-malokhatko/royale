#pragma once

#include "Node.hpp"

#include "ISelectedCard.hpp"
#include "IGameResolution.hpp"

namespace ui
{
	class GhostCard : public Node
	{
		ISelectedCard& mSelectedCard;
		IGameResolution& mGameResolution;

		Vector2 mMousePos{};

	public:
		GhostCard(ISelectedCard& card, IGameResolution& resolution);

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;

		void handleMove(MouseMoveEvent moveEvent) override;
	};
}