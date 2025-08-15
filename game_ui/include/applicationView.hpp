#pragma once

#include "view.hpp"
#include "gameRenderer.hpp"
#include "game.hpp"
#include "UICard.hpp"
#include "elixirBar.hpp"
#include <array>

class ApplicationView : public royale::View
{
	Vector2 mResolution;
	Rectangle mGameBounds;
	const char* mWindowTitle;

	int mTileSize {};
	Rectangle mControlPanel {};
	ElixirBar mElixirBar {};

	GameRenderer mGameRenderer {};
	TextureManager mTextureManager {};

	std::array<UICard, royale::Config::HAND_SIZE> mCards;
	std::vector<std::unique_ptr<royale::Event>> mEvents {};

private:
	bool isOnField(int x, int y);
	bool isOnField(Vector2 position);
	Vector2 toFieldCoords(Vector2 position);
	Vector2 toFieldCoords(int x, int y);

private:
	std::array<UICard, royale::Config::HAND_SIZE> initCards(const royale::Game& game);
	void drawGhost(const UICard& card);
	void onCardDropped(UICard& card);

public:
	ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game);
	~ApplicationView();

	void resize(float x, float y, const royale::Game& game) override;
	void update(const royale::Game& game) override;
	void render(const royale::Game& game) override;
	std::vector<std::unique_ptr<royale::Event>> pollEvents() override;
};
