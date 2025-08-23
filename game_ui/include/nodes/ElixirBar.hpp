#pragma once

#include "Node.hpp"
#include "colorScheme.hpp"
#include <string>
#include "config.hpp"

namespace ui
{
	class ElixirBar : public Node
	{
		const int fontSize = 28;
		double mMaxElixir = royale::Config::MAX_ELIXIR;
		double mElixir {};

	public:

		ElixirBar() = default;
		ElixirBar(Rectangle rec, double maxElixir, double elixir = 0);

		void draw() const override;
		void resize(int x, int y) override;

		void setElixir(double elixir);
		double getElixir() const;
	};
}