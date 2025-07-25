#pragma once

#include "view.hpp"
#include "gameRenderer.hpp"
#include "game.hpp"
#include "vector2.hpp"
#include "card.hpp"
#include "elixirBar.hpp"
#include "colorScheme.hpp"
#include <array>

class ApplicationView : public royale::View
{
	Vector2 mResolution;
	Rectangle mGameBounds;
	Rectangle mControlPanel {};
	int mTileSize {};
	const char* mWindowTitle;

	ElixirBar mElixirBar {};
	std::array<Card, royale::Config::CARD_NUMBER> mCards {};
	royale::GameRenderer* mGameRenderer {};
	std::vector<royale::Event*> mEvents {};

	bool isOnField(int x, int y);
	bool isOnField(Vector2 position);
	Vector2 toFieldCoords(Vector2 position);
	Vector2 toFieldCoords(int x, int y);

	void drawGhost(const Card& card);

public:
	ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game);
	~ApplicationView();

	void resize(float x, float y, const royale::Game& game) override;
	void update(const royale::Game& game) override;
	void render(const royale::Game& game) override;
	std::vector<royale::Event*> pollEvents() override;
};
