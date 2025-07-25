#pragma once

#include <array>
#include "vector2.hpp"
#include "UIElement.hpp"
#include "colorScheme.hpp"
#include "unitType.hpp"
//#include "textureManager.hpp"
#include "textureManager.hpp"

class Card : public UIElement
{
	// Default position is where card should be normally drawn
	// or where it should be drawn after the drag is over
	Vector2 mDefaultPosition{};
	royale::UnitType mUnitType{};

	bool mSelected{};
	bool mDragged{};
public:
	Card() = default;

	Card(Rectangle rec)
		: UIElement(rec)
	{
		mDefaultPosition = {rec.x, rec.y};
	}

	~Card() = default;

	void setDefaultPosition(Vector2 position)
	{
		mDefaultPosition = position;
	}

	void setUnitType(royale::UnitType unitType)
	{
		mUnitType = unitType;
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

		const Texture2D& texture = TextureManager::textures[mUnitType];
		//DrawTexture(texture, mRec.x, mRec.y, WHITE);
		Rectangle source = { 0, 0, mRec.width, mRec.height };
		DrawTextureRec(texture, source, Vector2{ mRec.x, mRec.y }, WHITE);
		//Color cardColor = mEnabled ? cardColors[mUnitType] : UIColorScheme.CARD_COLOR;
		//DrawRectangleRec(mRec, cardColor);
	}

	void onClick() override
	{
		mDragged = true;
	}

	void onRelease() override
	{
		mDragged = false;

		setPosition(mDefaultPosition);
	}	
};
