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


		//
		//	Generates events from input and passes them to children
		//
		virtual void handleInput() = 0;
	};
}