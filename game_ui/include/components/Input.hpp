#pragma once

#include "Node.hpp"

#include <string>

namespace ui
{
	class Input : public Node
	{
		std::string content{};
		int maxLength;

	public:
		Input(Rectangle rec, int maxLength = 20);

		void handleClick();

	};
}