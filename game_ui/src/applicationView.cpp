#include "applicationView.hpp"
#include "raylib.h"
#include "card.hpp"
#include "cardPlacedEvent.hpp"
#include "textureManager.hpp"
#include <algorithm>
#include <vector>
#include <array>
#include <cassert>
//

#include "GameScene.hpp"

//std::array<UICard, royale::Config::HAND_SIZE> ApplicationView::initCards(const royale::Game& game)
//{
//	std::array<UICard, royale::Config::HAND_SIZE> cards;
//	auto cardTypes = game.getCards();
//
//	int i = 0;
//	for (UICard& card : cards)
//	{
//		card.setDropCallback([this](UICard& card) {
//			this->onCardDropped(card);
//			});
//
//		royale::CardType cardType = cardTypes[i];
//
//		card.setCard(cardType);
//		card.setTexture(mTextureManager.GetTexture(cardType));
//		i++;
//	}
//
//	return cards;
//}

ApplicationView::ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game)
	:
	mResolution{ resolutionX, resolutionY },
	mWindowTitle{ windowTitle }
{
	InitWindow(resolutionX, resolutionY, windowTitle);

	Rectangle resolutionRect = { 0, 0, mResolution.x, mResolution.y };
	mCurScene = std::make_unique<ui::GameScene>(resolutionRect, game);
}

//ApplicationView::ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game)
//	: mResolution{ resolutionX, resolutionY},
//	mWindowTitle{ windowTitle }
//{
//	SetTraceLogLevel(LOG_WARNING);
//	InitWindow(resolutionX, resolutionY, windowTitle);
//	SetTargetFPS(60);
//
//	mTextureManager.LoadTextures();
//	mCards = initCards(game);
//
//	mGameRenderer.LoadTextures();
//
//	resize(mResolution.x, mResolution.y, game);
//}

//
//ApplicationView::~ApplicationView()
//{
//}

// TODO:
// remove magic numbers
void ApplicationView::resize(float x, float y, const royale::Game& game)
{
	mCurScene->resize(x, y);
}
//
//void ApplicationView::drawGhost(const UICard& card)
//{
//	Vector2 fieldPosition = toFieldCoords(GetMousePosition());
//
//	int absoluteX = mGameBounds.x + mTileSize * fieldPosition.x;
//	int absoluteY = mGameBounds.y + mTileSize * fieldPosition.y;
//
//	DrawRectangle(absoluteX, absoluteY, mTileSize, mTileSize, UIColorScheme.SELECTED_TILE_COLOR);
//}

void ApplicationView::render(const royale::Game& game)
{
	//RenderTexture2D gameTexture = LoadRenderTexture(mGameBounds.width, mGameBounds.height);
	//mGameRenderer.render(game, gameTexture);

	//BeginDrawing();
	//	ClearBackground(UIColorScheme.BACKGROUND_COLOR);

	//	// draw game to the window
	//	Rectangle source = { 0.0f, 0.0f, mGameBounds.width, -mGameBounds.height };
	//	Vector2 position = { mGameBounds.x, mGameBounds.y };
	//	DrawTextureRec(gameTexture.texture, source, position, WHITE);

	//	// draw control panel
	//	DrawRectangleRec(mControlPanel, UIColorScheme.CONTROL_PANEL_COLOR);

	//	// draw elixir bar
	//	mElixirBar.draw();

	//	// draw cards
	//	for (const UICard& card : mCards)
	//	{
	//		if (card.isDragged() && isOnField(GetMousePosition()))
	//		{
	//			drawGhost(card);
	//			continue;
	//		}

	//		card.draw();
	//	}

	//EndDrawing();

	//// unload the texture, free the memory
	//UnloadRenderTexture(gameTexture);
	BeginDrawing();
	mCurScene->draw();
	EndDrawing();
}

void ApplicationView::update(const royale::Game& game)
{
	//for (UICard& card : mCards)
	//{
	//	card.update();
	//	card.handleInput();
	//}

	//auto cards = game.getCards();
	//for (size_t i = 0; i < cards.size(); ++i)
	//{
	//	auto card = cards[i];
	//	auto& uiCard = mCards[i];

	//	if (uiCard.getCard() != card)
	//	{
	//		uiCard.setCard(card);
	//		uiCard.setTexture(mTextureManager.GetTexture(card));

	//		float cardWidth = mGameBounds.width / cards.size();
	//		float cardHeight = mControlPanel.height - mGameBounds.y * 2;

	//		uiCard.resizeTexture(cardWidth, cardHeight);
	//	}
	//}

	//mElixirBar.setElixir(game.getElixir());
}

std::vector<std::unique_ptr<royale::Event>>	ApplicationView::pollEvents()
{
	std::vector<std::unique_ptr<royale::Event>>vec{};
	return vec;
	//return std::move(mEvents);
}

// TODO
// Add more checks for the cards palcement
// when adding multiplayer it is important that client checks the validity of their own actions
// for smooth gameplay. Though this may perhaps be solved by rendering the unit in the game
// only after it was added by the game class itself.
//void ApplicationView::onCardDropped(UICard& card)
//{
//	if (isOnField(card.getCenter()))
//	{
//		Vector2 coords = toFieldCoords(card.getCenter());
//		royale::Vector2 position = { coords.x, coords.y };
//
//		auto event = std::make_unique<royale::CardPlacedEvent>(position, card.getCard());
//		mEvents.push_back(std::move(event));
//	}
//}



//
//bool isInRange(royale::Vector2 target, royale::Vector2 range)
//{
//	return target.x < range.x && target.x >= 0
//		&& target.y < range.y && target.y >= 0;
//}
//
//bool ApplicationView::isOnField(int x, int y)
//{
//	return x > mGameBounds.x && x < mGameBounds.x + mGameBounds.width &&
//		y > mGameBounds.y && y < mGameBounds.y + mGameBounds.height;
//}
//
//bool ApplicationView::isOnField(Vector2 position)
//{
//	return isOnField(position.x, position.y);
//}
//
//
//Vector2 ApplicationView::toFieldCoords(int x, int y)
//{
//	Vector2 position = { static_cast<float>(x), static_cast<float>(y) };
//	return toFieldCoords(position);
//}
//
//Vector2 ApplicationView::toFieldCoords(Vector2 position)
//{
//	position.x -= mGameBounds.x;
//	position.y -= mGameBounds.y;
//
//	position.x /= mTileSize;
//	position.y /= mTileSize;
//
//	position.x = static_cast<int>(position.x);
//	position.y = static_cast<int>(position.y);
//
//	return position;
//}