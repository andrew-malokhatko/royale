#include "LoadingScene.hpp"

namespace ui
{
	LoadingScene::LoadingScene(Rectangle rectangle, SceneManager& sceneManager)
		:
		Scene(rectangle, sceneManager),
		mLoadingIcon(Rectangle{ 0, 0, 0, 0 }, "loading", 2.0),
		mBackground{ mRec, "bg_loading" }
	{
		addChild(&mBackground);
		addChild(&mLoadingIcon);

		resize(rectangle.width, rectangle.height);
	}

	void LoadingScene::drawSelf() const
	{
		ClearBackground(WHITE);
	}
	
	void LoadingScene::resizeSelf(int width, int height)
	{
		static Vector2 LoadingIconPos = { 0.5, 0.5 };
		static Vector2 LoadingIconSize = { 0.2, 0.1 };

		mLoadingIcon.setPosition({ LoadingIconPos.x * width, LoadingIconPos.y * height });
		mLoadingIcon.resize(LoadingIconSize.x * width, LoadingIconSize.y * height);

		mBackground.resize(width, height);
	}
}