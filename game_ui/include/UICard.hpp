#pragma once

#include <array>
#include <functional>
#include "vector2.hpp"
#include "UIElement.hpp"
#include "colorScheme.hpp"
#include "CardType.hpp"
#include "textureManager.hpp"

class UICard : public UIElement
{
	// Default position is where card should be normally drawn
	// or where it should be drawn after the drag is over
	Vector2 mDefaultPosition{};
	Texture2D mTexture{};
	royale::CardType mCard{};

	std::function<void(UICard&)> dropCallback;

	bool mSelected{};
	bool mDragged{};
public:
	UICard() = default;

	UICard(Rectangle rec)
		: UIElement(rec)
	{
		mDefaultPosition = { rec.x, rec.y };
	}

	~UICard() = default;

	void setDefaultPosition(Vector2 position)
	{
		mDefaultPosition = position;
	}

	void setCard(royale::CardType card)
	{
		mCard = card;
	}

	void setTexture(const Texture2D& texture)
	{
		mTexture = texture;
	}

	royale::CardType getCard()
	{
		return mCard;
	}

	void update()
	{
		if (mDragged)
		{
			onDrag();
		}

		if (mDragged && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			onRelease();
		}
	}

	void resizeTexture(int width, int height)
	{
		Image image = LoadImageFromTexture(mTexture);
		ImageResize(&image, width, height);
		UnloadTexture(mTexture);
		mTexture = LoadTextureFromImage(image);
		UnloadImage(image);
	}

	void onDrag()
	{
		Vector2 mouse = GetMousePosition();
		float centeredX = mouse.x - mRec.width / 2;
		float centeredY = mouse.y - mRec.height / 2;
		setPosition({ centeredX, centeredY });
	}

	bool isDragged() const
	{
		return mDragged;
	}

	void draw() const override
	{
		if (!mVisible)
		{
			return;
		}

		Rectangle source = { 0, 0, mRec.width, mRec.height };

		DrawTextureRec(mTexture, source, Vector2{ mRec.x, mRec.y }, WHITE);
	}

	void onClick() override
	{
		mDragged = true;
	}

	void setDropCallback(std::function<void(UICard&)> func)
	{
		dropCallback = func;
	}

	void onRelease() override
	{
		dropCallback(*this);

		mDragged = false;

		setPosition(mDefaultPosition);
	}	
};
