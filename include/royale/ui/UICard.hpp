#pragma once

#include <array>
#include <functional>
#include "vector2.hpp"
#include "UIElement.hpp"
#include "colorScheme.hpp"
#include "card.hpp"
#include "textureManager.hpp"

class UICard : public UIElement
{
	// Default position is where card should be normally drawn
	// or where it should be drawn after the drag is over
	Vector2 mDefaultPosition{};
	royale::Card mCard{};

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

	void setCard(royale::Card card)
	{
		mCard = card;
	}

	royale::Card getCard()
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

		const Texture2D& texture = TextureManager::GetTexture(mCard);
		Rectangle source = { 0, 0, mRec.width, mRec.height };

		DrawTextureRec(texture, source, Vector2{ mRec.x, mRec.y }, WHITE);
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
