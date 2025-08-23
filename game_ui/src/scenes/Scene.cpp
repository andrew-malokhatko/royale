#include "Scene.hpp"

namespace ui
{
	void Scene::handleInput()
	{
		if (!isEnabled())
			return;

		if (CheckCollisionPointRec(GetMousePosition(), mRec))
		{
			onHover();

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				onClick();
			}

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				onRelease();
			}
		}
	}
}