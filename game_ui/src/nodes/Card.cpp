#include "Card.hpp"

namespace ui
{
	// Card implememntaiton

	Card::Card(royale::CardType card, Rectangle rectangle)
		:
		Node{rectangle},
		mCard{ card }
	{
	}

	void Card::draw() const
	{
		DrawRectangleRec(mRec, BLUE);
	}

	void Card::resize(int width, int height)
	{
		setSize({
			static_cast<float>(width),
			static_cast<float>(height)
			});
		

		// request new texture
	}

	//void Card::update()
	//{
	//	if (mDragged)
	//	{
	//		Vector2 mousePos = GetMousePosition();
	//		setPosition(mousePos);
	//	}
	//}

	//void Card::onClick()
	//{

	//	mSelected = true;
	//	mDragged = true;

	//	Node::onClick();
	//}

	//void Card::onRelease()
	//{

	//	mDragged = false;

	//	Node::onRelease();
	//}
}