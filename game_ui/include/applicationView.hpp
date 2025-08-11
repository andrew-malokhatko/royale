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
	Rectangle mControlPanel {};
	int mTileSize {};
	const char* mWindowTitle;

	ElixirBar mElixirBar {};
	std::array<UICard, royale::Config::HAND_SIZE> mCards {};
	royale::GameRenderer* mGameRenderer {};
	std::vector<std::unique_ptr<royale::Event>> mEvents {};

	bool isOnField(int x, int y);
	bool isOnField(Vector2 position);
	Vector2 toFieldCoords(Vector2 position);
	Vector2 toFieldCoords(int x, int y);

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
