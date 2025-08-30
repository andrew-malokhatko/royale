#pragma once

#include "Scene.hpp"
#include "components/Button.hpp"
#include "components/TextureComponent.hpp"

#include <string>

namespace ui
{
	class MainScene : public Scene
	{
		Button mPlayButton;
		TextureComponent mBackground;
		TextureComponent mArena;

		void findGame();

	public:
		MainScene(Rectangle rectangle, SceneManager& sceneManager);

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;
	};
}