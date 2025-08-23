#pragma once

#include "Node.hpp"

namespace ui
{
	class Scene : public Node
	{
	public:
		Scene(Rectangle rectangle)
			:
			Node(rectangle)
		{
		}


		// generates events and forwards them to children
		void handleInput();
	};
}