#pragma once

#include "raylib.h"

class UIElement
{
public:
	static const int SELECTED_CARD_OFFSET_MULTIPLIER = 0.1;

	Rectangle mRec {};
	bool mVisible = true;
	bool mEnabled = true;

	virtual void draw() const = 0;
	virtual void update() {};
	virtual void onClick() {};
	virtual void onRelease() {};
	virtual void onHover() {};

	UIElement() = default;

	UIElement(Rectangle rec, bool visible = true, bool enabled = true)
		: mRec{ rec },
		mVisible {visible},
		mEnabled {enabled}
	{
	}

	void handleInput()
	{
		if (!mVisible || !mEnabled)
			return;

		if (CheckCollisionPointRec(GetMousePosition(), mRec))
		{
			onHover();

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				onClick();
			}

			//if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			//{
			//	onRelease();
			//}
		}

	}

	Vector2 getPosition() const
	{
		return { mRec.x, mRec.y };
	}

	Vector2 getCenter() const
	{
		return { mRec.x + mRec.width / 2, mRec.y + mRec.height / 2 };
	}

	void setPosition(Vector2 position)
	{
		mRec.x = position.x;
		mRec.y = position.y;
	}

	Vector2 getSize() const
	{
		return { mRec.width, mRec.height };
	}

	void setSize(Vector2 size)
	{
		mRec.width = size.x;
		mRec.height = size.y;
	}

	bool collides(Vector2 point) const
	{
		return CheckCollisionPointRec(point, mRec);
	}

	bool isMouseOver() const
	{
		return(CheckCollisionPointRec(GetMousePosition(), mRec));
	}

	virtual ~UIElement() = default;
};