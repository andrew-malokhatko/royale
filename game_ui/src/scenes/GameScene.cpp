#include "GameScene.hpp"
#include "Config.hpp"
#include "MouseClickEvent.hpp"
#include "MouseReleaseEvent.hpp"
#include "MouseHoverEvent.hpp"
#include "CardPlacedEvent.hpp"
#include <cassert>

namespace ui
{
	bool GameScene::placeCard()
	{
		const Card* selectedCard = mCardHolder.getSelectedCard();
		assert(selectedCard);

		Vector2 mousePos = GetMousePosition();
		Vector2 fieldSize = mGameNode.getLayout();
		Vector2 cardGamePos = mGameNode.getTileFromPos(mousePos);

		royale::Vector2 royaleCardPos = { cardGamePos.x, cardGamePos.y };
		royale::CardType cardType = selectedCard->getCardType();

		// Check if card was placed inside the game bounds
		if (royaleCardPos.x < 0 || royaleCardPos.x > fieldSize.x ||
			royaleCardPos.y < 0 || royaleCardPos.y > fieldSize.y)
			return false;

		mGameEvents.push_back(std::make_unique<royale::CardPlacedEvent>(royaleCardPos, cardType));
		return true;
	}

	GameScene::GameScene(Rectangle rectangle, const royale::Game& game)
		:
		Scene(rectangle),
		mGame{ game },
		mCardHolder(Rectangle{ 0, 0, 0, 0 }, game),
		mElixirBar(Rectangle{ 0, 0, 0, 0 }, royale::Config::MAX_ELIXIR, 0.0),
		mGameNode(Rectangle{ 0, 0, 0, 0 }, game),
		mGhostCard(mCardHolder, mGameNode)
	{
		addChild(&mElixirBar);
		addChild(&mGameNode);
		addChild(&mCardHolder);
		addChild(&mGhostCard);

        mCardHolder.setCardDroppedCallback([this]() -> bool { return placeCard(); });

		resize(rectangle.width, rectangle.height);
	}

	void GameScene::drawSelf() const
	{
		ClearBackground(BLACK);
	}

	void GameScene::resizeSelf(int width, int height)
	{
		// percentages for placing everything (based on the scenes width and height)
		static const Vector2 CardHolderPos = { 0.0, 0.8 };
		static const Vector2 CardHolderSize = { 1.0, 0.2 };
		static const Vector2 ElixirBarPos = { 0.0, 0.775 };
		static const Vector2 ElixirBarSize = { 1.0, 0.025 };
		static const Vector2 GameNodePos = { 0.1, 0.05 };
		static const Vector2 GameNodeSize = { 0.8, 0.7 };

		mCardHolder.setPosition({ CardHolderPos.x * width, CardHolderPos.y * height });
		mElixirBar.setPosition({ ElixirBarPos.x * width, ElixirBarPos.y * height });
		mGameNode.setPosition({ GameNodePos.x * width, GameNodePos.y * height });

		mCardHolder.resize(CardHolderSize.x * width, CardHolderSize.y * height);
		mElixirBar.resize(ElixirBarSize.x * width, ElixirBarSize.y * height);
		mGameNode.resize(GameNodeSize.x * width, GameNodeSize.y * height);
	}

	void GameScene::updateSelf()
	{
		mCardHolder.updateState(mGame);
		mElixirBar.updateState(mGame);
	}
}