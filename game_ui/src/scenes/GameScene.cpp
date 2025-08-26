#include "GameScene.hpp"
#include "Config.hpp"

namespace ui
{
	GameScene::GameScene(Rectangle rectangle, const royale::Game& game)
		:
		Scene(rectangle),
		mGame{ game },
		mCardHolder(Rectangle{ 0, 0, 0, 0 }, game),
		mElixirBar(Rectangle{ 0, 0, 0, 0 }, royale::Config::MAX_ELIXIR, 0.0),
		mGameNode(Rectangle{ 0, 0, 0, 0 }, game)
	{
		addChild(&mCardHolder);
		addChild(&mElixirBar);
		addChild(&mGameNode);

		resize(rectangle.width, rectangle.height);
	}

	void GameScene::drawSelf() const
	{
		// nothing
	}

	void GameScene::resizeSelf(int width, int height)
	{
		// percentages for placing everything (based on the scenes width and height)
		static const Vector2 CardHolderPos = { 0.0, 0.8 };
		static const Vector2 CardHolderSize = { 1.0, 0.2 };
		static const Vector2 ElixirBarPos = { 0.0, 0.775 };
		static const Vector2 ElixirBarSize = { 1.0, 0.025 };
		static const Vector2 GameNodePos = { 0.1, 0.05 };
		static const Vector2 GameNodeSize = { 0.8, 0.7 };

		mCardHolder.setPosition({ CardHolderPos.x * width, CardHolderPos.y * height });
		mElixirBar.setPosition({ ElixirBarPos.x * width, ElixirBarPos.y * height });
		mGameNode.setPosition({ GameNodePos.x * width, GameNodePos.y * height });

		mCardHolder.resize(CardHolderSize.x * width, CardHolderSize.y * height);
		mElixirBar.resize(ElixirBarSize.x * width, ElixirBarSize.y * height);
		mGameNode.resize(GameNodeSize.x * width, GameNodeSize.y * height);
	}
}