#pragma once

#include "Scene.hpp"
#include "components/LoadingIcon.hpp"
#include "components/TextureComponent.hpp"

namespace ui
{
	class LoadingScene : public Scene
	{
		LoadingIcon mLoadingIcon;
		TextureComponent mBackground;

	public:
		LoadingScene(Rectangle rectangle, SceneManager& sceneManager);

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;
	};
}