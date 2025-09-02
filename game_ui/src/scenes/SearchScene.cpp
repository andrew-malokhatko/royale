#include "SearchScene.hpp"

namespace ui
{
	void SearchScene::stopSearch()
	{
		// other logic is handled in onSceneLeave method (e.g client disconnect)
		mSceneManager.setScene("main");
	}

	SearchScene::SearchScene(Rectangle rectangle, Net::Client& client, SceneManager& sceneManager)
		:
		Scene(rectangle, sceneManager),
		mClient(client),
		mStopSearchButton(Rectangle{ 0, 0, 0, 0 }, "Cancel", [this]() {stopSearch(); }),
		mLoadingIcon(Rectangle{ 0, 0, 0, 0 }, "loading", 0.2),
		mBackground{ mRec, "bg" }
	{
		addChild(&mBackground);
		addChild(&mStopSearchButton);
		addChild(&mLoadingIcon);

		resize(rectangle.width, rectangle.height);
	}

	void SearchScene::drawSelf() const
	{
		ClearBackground(BLACK);
	}

	void SearchScene::resizeSelf(int width, int height)
	{
		static Vector2 SearchButtonPos = { 0.3, 0.7 };
		static Vector2 SearchButtonSize = { 0.4, 0.1 };
		static Vector2 LoadingIconPos = { 0.5, 0.3 };
		static Vector2 LoadingIconSize = { 0.2, 0.1 };

		mStopSearchButton.setPosition({ SearchButtonPos.x * width, SearchButtonPos.y * height });
		mStopSearchButton.resize(SearchButtonSize.x * width, SearchButtonSize.y * height);

		mLoadingIcon.setPosition({ LoadingIconPos.x * width, LoadingIconPos.y * height });
		mLoadingIcon.resize(LoadingIconSize.x * width, LoadingIconSize.y * height);

		mBackground.resize(width, height);
	}

	void SearchScene::onSceneLoad()
	{
		// possible move to separate thread
		//mClient.startConnection();
	}

	void SearchScene::onSceneLeave()
	{
		mClient.endConnection();
	}
}

