#include "Scene.hpp"

namespace ui
{
	void Scene::handleInput()
	{
		static Vector2 prevMouse = { 0, 0 };

		Vector2 mouse = GetMousePosition();
		int mouseX = mouse.x;
		int mouseY = mouse.y;

		if (mouse.x != prevMouse.x ||
			mouse.y != prevMouse.y)
		{
			onMove(MouseMoveEvent{ mouseX, mouseY });
		}

		if (this->collides(mouse))
		{
			onHover(MouseHoverEvent{ mouseX, mouseY });

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				onClick(MouseClickEvent{ mouseX, mouseY });
			}

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				onRelease(MouseReleaseEvent{ mouseX, mouseY });
			}
		}

		prevMouse = mouse;
	}
}