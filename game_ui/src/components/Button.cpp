#include "components/Button.hpp"

namespace ui
{
	Button::Button(Rectangle rec, std::string text, std::function<void(void)> callback)
		:
		Node(rec),
		mText{ text },
		mCallback{callback}
	{
	}

	void Button::drawSelf() const
	{
		DrawRectangle(0, 0, mRec.width, mRec.height, mColor);

		int fontSize = mRec.width / mText.size();
		int textWidth = fontSize * mText.size() / 2;	// text width is 2 times smaller than it's height
		int textHeight = fontSize;

		int textX = (mRec.width - textWidth) / 2;
		int textY = (mRec.height - textHeight) / 2;

		DrawText(mText.c_str(), textX, textY, fontSize, WHITE);
	}

	void Button::resizeSelf(int width, int height)
	{
		setSize({ static_cast<float>(width), static_cast<float>(height) });
	}

	void Button::setCallback(std::function<void(void)> callback)
	{
		mCallback = callback;
	}

	void Button::handleClick(MouseClickEvent)
	{
		mCallback();
	}

	void Button::handleHover(MouseHoverEvent)
	{
		mColor = BLUE;
	}
}