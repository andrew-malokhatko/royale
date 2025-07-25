#pragma once

#include "UIElement.hpp"
#include "colorScheme.hpp"
#include "config.hpp"
#include <string>

class ElixirBar : public UIElement
{
	const int fontSize = 28;
	double mMaxElixir = royale::Config::MAX_ELIXIR;
	double mElixir {};

public:

	ElixirBar() = default;

	ElixirBar(Rectangle rec, double maxElixir, double elixir = 0)
		:UIElement(rec),
		mMaxElixir{ maxElixir },
		mElixir{ elixir }
	{
	}

	void draw() const override
	{
		// draw background
		DrawRectangleRec(mRec, UIColorScheme.ELIXIR_BAR_COLOR);

		// draw elixir
		Rectangle elixirRec = mRec;
		elixirRec.width *= mElixir / mMaxElixir;
		DrawRectangleRec(elixirRec, UIColorScheme.ELIXIR_COLOR);

		// draw separators
		double elixirWidth = mRec.width / mMaxElixir;
		double startY = mRec.y;
		double endY = startY + mRec.height;
		for (int i = 1; i < mMaxElixir; i++)
		{
			int posX = mRec.x + elixirWidth * i;
			DrawLine(posX, startY, posX, endY, UIColorScheme.ELIXIR_DIVISORS_COLOR);
		}

		// draw elixir number(text)
		int elixir = mElixir;
		std::string elixirText = std::to_string(elixir);
		Vector2 textPosition = {
			mRec.x + mRec.width - elixirWidth / 2,
			mRec.y
		};
		DrawText(elixirText.data(), textPosition.x, textPosition.y, fontSize, UIColorScheme.ELIXIR_DIVISORS_COLOR);
	}

	void setElixir(double elixir)
	{
		mElixir = elixir;
	}
};