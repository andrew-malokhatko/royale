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
		if (mSelected && !mDragged)
		{
			float forward = mRec.height / 10;
			DrawTexture(mTexture, 0, -forward, WHITE);
		}
		else
		{
			DrawTexture(mTexture, 0, 0, WHITE);
		}
	}

	void Card::resizeSelf(int width, int height)
	{
		setSize({
			static_cast<float>(width),
			static_cast<float>(height)
			});

		loadTexture();
	}

	void Card::select()
	{
		mSelected = true;
	}

	void Card::deselect()
	{
		mSelected = false;
	}

	void Card::startDrag()
	{
		mDragged = true;
	}
	void Card::stopDrag()
	{
		mDragged = false;
	}

	bool Card::isDragged() const
	{
		return mDragged;
	}

	bool Card::isSelected() const
	{
		return mSelected;
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