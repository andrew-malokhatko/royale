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

	void ElixirBar::drawSelf() const
	{
		// draw background
		DrawRectangle(0, 0, mRec.width, mRec.height, UIColorScheme.ELIXIR_BAR_COLOR);

		// draw elixir
		float full = (mElixir / mMaxElixir);
		float elixirWidth = mRec.width * full;
		DrawRectangle(0, 0, elixirWidth, mRec.height, UIColorScheme.ELIXIR_COLOR);

		// draw separators
		float dropWidth = mRec.width / mMaxElixir;
		for (int i = 1; i < mMaxElixir; i++)
		{
			int posX = dropWidth * i;
			DrawLine(posX, 0, posX, mRec.height, UIColorScheme.ELIXIR_DIVISORS_COLOR);
		}

		// draw elixir number(text)
		int elixir = mElixir;
		std::string elixirText = std::to_string(elixir);
		float textX = mRec.width - dropWidth / 2;
		DrawText(elixirText.data(), textX, 0, fontSize, UIColorScheme.ELIXIR_DIVISORS_COLOR);
	}

	void ElixirBar::resizeSelf(int width, int height)
	{
		setSize({ static_cast<float>(width), static_cast<float>(height) });
	}

	void ElixirBar::setElixir(double elixir)
	{
		mElixir = elixir;
	}
}