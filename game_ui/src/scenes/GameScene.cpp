#include "GameScene.hpp"
#include "Config.hpp"

namespace ui
{
	GameScene::GameScene(Rectangle rectangle, const royale::Game& game)
		:
		Scene(rectangle),
		mCardHolder(Rectangle{0, 0, 0, 0}, game),
		mElixirBar(Rectangle{0, 0, 0, 0}, royale::Config::MAX_ELIXIR, 0.0)
	{
		addChild(&mCardHolder);
		addChild(&mElixirBar);

		resize(rectangle.width, rectangle.height);
	}

	void GameScene::draw() const
	{
		BeginDrawing();

		for (const auto& child : mChildren)
		{
			child->draw();
		}

		EndDrawing();
	}

	void GameScene::resize(int width, int height)
	{
		// percentages for placing everything (based on the scenes width and height)
		static const Vector2 CardHolderPos = { 0.0, 0.8 };
		static const Vector2 CardHolderSize = { 1.0, 0.2 };
		static const Vector2 ElixirBarPos = { 0.0, 0.775 };
		static const Vector2 ElixirBarSize = { 1.0, 0.025 };

		mCardHolder.setPosition({ CardHolderPos.x * width, CardHolderPos.y * height });
		mElixirBar.setPosition({ ElixirBarPos.x * width, ElixirBarPos.y * height });

		mCardHolder.resize(CardHolderSize.x * width, CardHolderSize.y * height);
		mElixirBar.resize(ElixirBarSize.x * width, ElixirBarSize.y * height);
	}
}