#include "Card.hpp"
#include "textureManager.hpp"

namespace ui
{
	void Card::loadTexture()
	{
		auto& textureManager = TextureManager::getInstance();
		const auto& texture = textureManager.getTexture(mCard);

		Image image = LoadImageFromTexture(texture);
		ImageResize(&image, mRec.width, mRec.height);

		UnloadTexture(mTexture);
		mTexture = LoadTextureFromImage(image);

		UnloadImage(image);
	}

	Card::Card(royale::CardType card, Rectangle rectangle)
		:
		Node{ rectangle },
		mCard{ card }
	{
	}

	Card::~Card()
	{
		UnloadTexture(mTexture);
	}

	void Card::drawSelf() const
	{
		DrawTexture(mTexture, 0, 0, WHITE);
		//DrawRectangleRec(mRec, BLUE);
	}

	void Card::resizeSelf(int width, int height)
	{
		setSize({
			static_cast<float>(width),
			static_cast<float>(height)
			});

		loadTexture();
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