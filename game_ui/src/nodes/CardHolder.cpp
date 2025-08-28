#include "CardHolder.hpp"

namespace ui
{
	std::vector<Card> initCards(const royale::Game& game)
	{
		auto cardTypes = game.getCards();
		std::vector<Card> cards{};
		cards.reserve(cardTypes.size());

		for (auto type : cardTypes)
		{
			// place cards at 0, 0, as the will be placed correctly by the resize
			cards.emplace_back(type, Rectangle{ 0, 0, 0, 0 });
		}

		return cards;
	}

	Card initNextCard(const royale::Game& game)
	{
		return Card{ game.getNextCard(), Rectangle {0, 0, 0, 0} };
	}

	CardHolder::CardHolder(Rectangle rectangle, const royale::Game& game)
		:
		Node{ rectangle },
		mCards{ initCards(game) },
		mNextCard{ initNextCard(game) }
	{
		for (Card& card : mCards)
		{
			addChild(&card);
		}
		addChild(&mNextCard);

		resize(rectangle.width, rectangle.height);
	}

	void CardHolder::drawSelf() const
	{
		DrawRectangle(0, 0, mRec.width, mRec.height, GRAY);
	}

	void CardHolder::resizeSelf(int width, int height)
	{
		// constants in percentages (not ideal, but fast and easy to understand)
		static const Vector2 FirstCardPos = { 0.15, 0.05 };
		static const Vector2 CardSize = { 0.2, 0.9 };
		static const Vector2 NextCardPos = { 0.025, 0.5 };
		static const Vector2 NextCardSize = { 0.1, 0.45 };
		static const float CardSpace = 0.05;

		setSize({ static_cast<float>(width), static_cast<float>(height) });

		mNextCard.setPosition({ NextCardPos.x * width,  NextCardPos.y * height });
		mNextCard.resize(NextCardSize.x * width, NextCardSize.y * height);

		float offsetX = FirstCardPos.x * width;
		float cardY = FirstCardPos.y * height;
		for (size_t i = 0; i < mCards.size(); ++i)
		{
			Card& card = mCards[i];
			float cardX = CardSize.x * i * (CardSpace * width + width) + offsetX;

			card.resize(CardSize.x * width, CardSize.y * height);
			card.setPosition({ cardX, cardY });
		}
	}

	// Deselect card (bad solution)
	// Requires refactoring
	void CardHolder::updateSelf()
	{
		if (selectedCard && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			// call callback function before the selectedCard is set to nullptr
			bool cardPlaced{};
			if (onCardDropped)
			{
				cardPlaced = onCardDropped();
			}

			selectedCard->stopDrag();
			selectedCard->setVisible(true);
			selectedCard->setPosition(selectedCardPos);

			if (cardPlaced)
			{
				selectedCard->deselect();
				selectedCard = nullptr;
			}
		}
	}

	void CardHolder::updateState(const royale::Game & game)
	{
		// Update cards
		auto handCardTypes = game.getCards();
		for (size_t i = 0; i < handCardTypes.size(); ++i)
		{
			auto cardType = handCardTypes[i];
			auto& card = mCards[i];

			if (card.getCardType() != cardType)
			{
				card.setCard(cardType);
			}
		}

		// Update next card
		auto nextCardType = game.getNextCard();
		if (mNextCard.getCardType() != nextCardType)
		{
			mNextCard.setCard(nextCardType);
		}
	}

	void CardHolder::handleClick(MouseClickEvent mouseClick)
	{
		Vector2 mouse = { static_cast<float>(mouseClick.x), static_cast<float>(mouseClick.y) };

		mouse.x -= mRec.x;
		mouse.y -= mRec.y;

		for (Card& card : mCards)
		{
			if (card.collides(mouse))
			{
				selectedCard = &card;
				selectedCard->select();
				selectedCard->startDrag();
				selectedCardPos = selectedCard->getPosition();
				continue;
			}
			
			card.deselect();
		}
	}

	void CardHolder::handleMove(MouseMoveEvent mouseMove)
	{
		mouseMove.x -= mRec.x;
		mouseMove.y -= mRec.y;

		if (selectedCard && selectedCard->isDragged())
		{
			float x = static_cast<float>(mouseMove.x);
			float y = static_cast<float>(mouseMove.y);
			selectedCard->setCenter({ x, y });
		}
	}

	const Card* CardHolder::getSelectedCard()
	{
		return selectedCard;
	}

	void CardHolder::hideSelectedCard()
	{
		selectedCard->setVisible(false);
	}

	void CardHolder::showSelectedCard()
	{
		selectedCard->setVisible(true);
	}

	void CardHolder::setCardDroppedCallback(std::function<bool(void)> dropCallback)
	{
		onCardDropped = dropCallback;
	}
}