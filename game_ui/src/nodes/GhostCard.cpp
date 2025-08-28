#include "GhostCard.hpp"


namespace ui
{
	GhostCard::GhostCard(ISelectedCard& card, IGameResolution& resolution)
		:
		Node{ Rectangle {0, 0, 0, 0} },
		mSelectedCard{ card },
		mGameResolution{ resolution }
	{
	}

	static bool collidesPointRec(const Vector2& vec, const Rectangle& rec)
	{
		return vec.x >= rec.x && vec.x <= rec.x + rec.width &&
			vec.y >= rec.y && vec.y <= rec.y + rec.height;
	}

	void GhostCard::drawSelf() const
	{
		const Card* selectedCard = mSelectedCard.getSelectedCard();
		Rectangle viewport = mGameResolution.getViewPort();
		Vector2 gameSize = mGameResolution.getLayout();

		if (!selectedCard)
		{
			return;
		}

		if (collidesPointRec(mMousePos, viewport))
		{
			if (selectedCard->isDragged())
			{
				mSelectedCard.hideSelectedCard();
			}

			Vector2 tileSize = { viewport.width / gameSize.x, viewport.height / gameSize.y };
			Vector2 relativeMousePos = { mMousePos.x - viewport.x, mMousePos.y - viewport.y };

			int ghostX = relativeMousePos.x / tileSize.x;
			int ghostY = relativeMousePos.y / tileSize.y;

			int realX = ghostX * tileSize.x + viewport.x;
			int realY = ghostY * tileSize.y + viewport.y;

			DrawRectangle(realX, realY, tileSize.x, tileSize.y, BLUE);
		}
		else
		{
			mSelectedCard.showSelectedCard();
		}
	}

	void GhostCard::resizeSelf(int width, int height)
	{
		// do nothign
	}

	void GhostCard::handleMove(MouseMoveEvent moveEvent)
	{
		mMousePos = { static_cast<float>(moveEvent.x), static_cast<float>(moveEvent.y) };
	}
}