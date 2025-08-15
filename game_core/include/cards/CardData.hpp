#pragma once

#include "Card.hpp"
#include <string_view>
#include <unordered_map>

namespace royale
{
	//
	//	Converts CardType to string (also indicates filepath to the card)
	//
	extern const std::unordered_map<CardType, std::string_view> STRING_FROM_CARD;

	//
	//	Converts string to CardType (mainly used to deserialize from json)
	//
	extern const std::unordered_map<std::string_view, CardType> CARD_FROM_STRING;

	//
	//	Holds data about all cards in the game
	//
	extern const std::unordered_map<CardType, Card> CARD_DATA;
}