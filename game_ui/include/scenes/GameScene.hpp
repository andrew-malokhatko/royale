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

		bool placeCard();

	public:
		GameScene(Rectangle rectangle, SceneManager& sceneManager, const royale::Game& game);
		 
		void drawSelf() const override;
		void resizeSelf(int width, int height) override;
		void updateSelf() override;
	};
}