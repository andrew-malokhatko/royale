#pragma once
#include <stdexcept>
#include <cassert>

namespace royale
{
	enum class Rarity
	{
		Common,
		Rare,
		Epic,
		Legendary,
		Champion,
	};

	inline Rarity rarityFromString(const std::string& str)
	{
		if (str == "common")	return Rarity::Common;
		if (str == "rare")		return Rarity::Rare;
		if (str == "epic")		return Rarity::Epic;
		if (str == "legendary")	return Rarity::Legendary;
		if (str == "champion")	return Rarity::Champion;
		
		assert(false);
		throw new std::invalid_argument("Rarity cannot be constructred from: " + str);
	}
}