#include "applicationView.hpp"
#include "raylib.h"
#include "unit.hpp"
#include "card.hpp"
#include "cardPlacedEvent.hpp"
#include "textureManager.hpp"
#include <algorithm>
#include <vector>
#include <array>
#include <cassert>

ApplicationView::ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game)
	: mResolution{ resolutionX, resolutionY},
	mWindowTitle{ windowTitle }
{
	InitWindow(resolutionX, resolutionY, windowTitle);
	SetTargetFPS(60);
	TextureManager::LoadTextures();

	mGameRenderer = new royale::GameRenderer();
	resize(mResolution.x, mResolution.y, game);
	mEvents.reserve(10);

	// remove to somewhere else
	int i = 0;
	for (royale::Card unitType : game.getCards())
	{
		mCards[i].setDropCallback([this](UICard& card) {
			this->onCardDropped(card);
		});

		mCards[i].setCard(unitType);
		i++;
	}
}


ApplicationView::~ApplicationView()
{
	TextureManager::UnloadTextures();
}

// TODO:
// remove magic numbers
void ApplicationView::resize(float x, float y, const royale::Game& game)
{
	// Update variables
	mResolution = { x, y };
	mTileSize = (mResolution.y * 2.2 / 3) / game.getFieldSize().y;
	mGameBounds.width = mTileSize * game.getFieldSize().x;
	mGameBounds.height = mTileSize * game.getFieldSize().y;
	mGameBounds.x = (mResolution.x - mGameBounds.width) / 2;
	mGameBounds.y = (mResolution.y - mGameBounds.height) / 6;

	// Update control panel
	mControlPanel.x = 0;
	mControlPanel.y = mGameBounds.height + mGameBounds.y;
	mControlPanel.width = mResolution.x;
	mControlPanel.height = mResolution.y - mControlPanel.y;

	// Update elixir bar
	mElixirBar.setPosition(Vector2{ mControlPanel.x, mControlPanel.y });
	mElixirBar.setSize(Vector2{ mControlPanel.width, mControlPanel.height / 10 });

	// udpate cards
	int cardNumber = mCards.size();
	float cardWidth = mGameBounds.width / cardNumber;
	float cardHeight = mControlPanel.height - mGameBounds.y * 2;

	TextureManager::ResizeCards(cardWidth, cardHeight);

	for (int i = 0; i < cardNumber; i++)
	{
		UICard& card = mCards[i];

		float cardX = mControlPanel.x + i * cardWidth + ((i + 1 / cardNumber) * (cardWidth / cardNumber));
		float cardY = mControlPanel.y + mGameBounds.y;

		card.setPosition({ cardX, cardY });
		card.setDefaultPosition({ cardX, cardY });
		card.setSize({ cardWidth, cardHeight });
	}
}

void ApplicationView::drawGhost(const UICard& card)
{
	Vector2 fieldPosition = toFieldCoords(GetMousePosition());

	int absoluteX = mGameBounds.x + mTileSize * fieldPosition.x;
	int absoluteY = mGameBounds.y + mTileSize * fieldPosition.y;

	DrawRectangle(absoluteX, absoluteY, mTileSize, mTileSize, UIColorScheme.SELECTED_TILE_COLOR);
}

void ApplicationView::render(const royale::Game& game)
{
	RenderTexture2D gameTexture = LoadRenderTexture(mGameBounds.width, mGameBounds.height);
	mGameRenderer->render(game, gameTexture);

	BeginDrawing();
		ClearBackground(UIColorScheme.BACKGROUND_COLOR);

		// draw game to the window
		Rectangle source = { 0.0f, 0.0f, mGameBounds.width, -mGameBounds.height };
		Vector2 position = { mGameBounds.x, mGameBounds.y };
		DrawTextureRec(gameTexture.texture, source, position, WHITE);

		// draw control panel
		DrawRectangleRec(mControlPanel, UIColorScheme.CONTROL_PANEL_COLOR);

		// draw elixir bar
		mElixirBar.draw();

		// draw cards
		for (const UICard& card : mCards)
		{
			if (card.isDragged() && isOnField(GetMousePosition()))
			{
				drawGhost(card);
				continue;
			}

			card.draw();
		}

	EndDrawing();

	// unload the texture, free the memory
	UnloadRenderTexture(gameTexture);
}

void ApplicationView::update(const royale::Game& game)
{
	for (UICard& card : mCards)
	{
		card.update();
		card.handleInput();
	}

	mElixirBar.setElixir(game.getElixir());
}

// TODO
// Add more checks for the cards palcement
// when adding multiplayer it is important that client checks the validity of their own actions
// for smooth gameplay. Though this may perhaps be solved by rendering the unit in the game
// only after it was added by the game class itself.
void ApplicationView::onCardDropped(UICard& card)
{
	if (isOnField(card.getCenter()))
	{
		Vector2 coords = toFieldCoords(card.getCenter());
		royale::Vector2 position = { coords.x, coords.y };

		royale::Event* event = new royale::CardPlacedEvent(position, card.getCard());
		mEvents.push_back(event);
	}
}

std::vector<royale::Event*>	ApplicationView::pollEvents()
{	
	return std::move(mEvents);
}

bool isInRange(royale::Vector2 target, royale::Vector2 range)
{
	return target.x < range.x && target.x >= 0
		&& target.y < range.y && target.y >= 0;
}

bool ApplicationView::isOnField(int x, int y)
{
	return x > mGameBounds.x && x < mGameBounds.x + mGameBounds.width &&
		y > mGameBounds.y && y < mGameBounds.y + mGameBounds.height;
}

bool ApplicationView::isOnField(Vector2 position)
{
	return isOnField(position.x, position.y);
}


Vector2 ApplicationView::toFieldCoords(int x, int y)
{
	Vector2 position = { static_cast<double>(x), static_cast<double>(y) };
	return toFieldCoords(position);
}

Vector2 ApplicationView::toFieldCoords(Vector2 position)
{
	position.x -= mGameBounds.x;
	position.y -= mGameBounds.y;

	position.x /= mTileSize;
	position.y /= mTileSize;

	position.x = static_cast<int>(position.x);
	position.y = static_cast<int>(position.y);

	return position;
}