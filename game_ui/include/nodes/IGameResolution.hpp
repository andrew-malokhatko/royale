#pragma once

#include "raylib.h"

namespace ui
{
	class IGameResolution
	{
	public:
		//
		//	Return absolute size and positioning of the game
		//
		virtual Rectangle getViewPort() = 0;

		//
		//	Return relative size of the game in tiles
		//
		virtual Vector2 getLayout() = 0;
	};
}