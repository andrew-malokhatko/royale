#pragma once

#include "game.hpp"
#include "Scene.hpp"
#include "ElixirBar.hpp"
#include "CardHolder.hpp"
#include "GameNode.hpp"
#include "GhostCard.hpp"

namespace ui
{
	class GameScene : public Scene
	{
		const royale::Game& mGame;

		CardHolder mCardHolder;
		ElixirBar mElixirBar;
		GameNode mGameNode;
		GhostCard mGhostCard;

	public:
		GameScene(Rectangle rectangle, const royale::Game& game);
		 
		void drawSelf() const override;
		void resizeSelf(int width, int height) override;
		void handleInput() override;
	};
}