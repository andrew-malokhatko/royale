#include "ElixirBar.hpp"

namespace ui
{
	ElixirBar::ElixirBar(Rectangle rec, double maxElixir, double elixir)
		:
		Node(rec),
		mMaxElixir{ maxElixir },
		mElixir{ elixir }
	{
	}

	void ElixirBar::draw() const
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
			static_cast<float>(mRec.x + mRec.width - elixirWidth / 2),
			mRec.y
		};
		DrawText(elixirText.data(), textPosition.x, textPosition.y, fontSize, UIColorScheme.ELIXIR_DIVISORS_COLOR);
	}

	void ElixirBar::resize(int width, int height)
	{
		setSize({ static_cast<float>(width), static_cast<float>(height) });
	}

	void ElixirBar::setElixir(double elixir)
	{
		mElixir = elixir;
	}
}