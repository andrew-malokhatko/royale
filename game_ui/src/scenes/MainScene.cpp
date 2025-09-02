#pragma once

#include "MainScene.hpp"
#include <iostream>

namespace ui
{
	void MainScene::findGame()
	{
		std::cout << "Find game button triggered" << "\n";
		mSceneManager.setScene("search");
	}

    MainScene::MainScene(Rectangle rectangle, SceneManager& sceneManager)
		:
		Scene(rectangle, sceneManager),
		mPlayButton{ Rectangle{0, 0, 0, 0}, "Button", [this]() { findGame(); }},
		mBackground{ mRec, "bg"},
		mArena{ Rectangle{0, 0, 0, 0}, "ice_arena"}
    {
		addChild(&mBackground);
		addChild(&mPlayButton);
		addChild(&mArena);

		resize(rectangle.width, rectangle.height);
    }

	void MainScene::drawSelf() const
	{
		// nothing
	}
	void MainScene::resizeSelf(int width, int height)
	{
		static Vector2 PlayButtonPos = { 0.3, 0.7 };
		static Vector2 PlayButtonSize = { 0.4, 0.1 };
		static Vector2 ArenaPos = { 0.2, 0.3 };
		static Vector2 ArenaSize = { 0.6, 0.3 };

		mPlayButton.setPosition({ width * PlayButtonPos.x, height * PlayButtonPos.y });
		mArena.setPosition({ width * ArenaPos.x, height * ArenaPos.y });

		mPlayButton.resize(PlayButtonSize.x * width, PlayButtonSize.y * height);
		mArena.resize(ArenaSize.x * width, ArenaSize.y * height);
		mBackground.resize(width, height);
	}
}