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
		return Card{ game.getNextCard(), Rectangle {0, 0, 0, 0}};
	}

	CardHolder::CardHolder(Rectangle rectangle, const royale::Game& game)
		:
		Node{rectangle},
		mCards{initCards(game)},
		mNextCard{initNextCard(game)}
	{
		for (Card& card: mCards)
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

		mNextCard.setPosition({ NextCardPos.x * width,  NextCardPos.y * height});
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


	//void CardHolder::update()
	//{
	//	for (Card& card : mCards)
	//	{
	//		card.update();
	//	}
	//}

	//void CardHolder::onClick()
	//{
	//	
	//}

	//void CardHolder::onRelease()
	//{
	//	
	//}
}