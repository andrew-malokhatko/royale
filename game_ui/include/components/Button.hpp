#pragma once

#include "Node.hpp"
#include <functional>
#include <string>

namespace ui
{
	class Button : public Node
	{
		std::function<void(void)> mCallback;
		std::string mText;
		Color mColor = GREEN;

	public:
		Button(Rectangle rec, std::string text = "Button", std::function<void(void)> callback = {});

		void drawSelf() const override;
		void resizeSelf(int width, int hegiht) override;

		void setCallback(std::function<void(void)> callback);
		void handleClick(MouseClickEvent) override;
		void handleHover(MouseHoverEvent) override;
	};
}