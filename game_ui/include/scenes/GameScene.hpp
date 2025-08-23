#pragma once

#include "game.hpp"
#include "Scene.hpp"
#include "ElixirBar.hpp"
#include "CardHolder.hpp"


namespace ui
{
	class GameScene : public Scene
	{
		
		royale::Game game;

		CardHolder mCardHolder;
		ElixirBar mElixirBar;

		//GameRenderer mGameRenderer{};

	public:
		GameScene(Rectangle rectangle, const royale::Game& game);
		 
		void draw() const override;
		void resize(int width, int height) override;
	};
}