#pragma once

#include <stdexcept>
#include <cassert>

namespace royale
{
	enum class PlacementType
	{
		Troop,		// only on the friend side of the field
		TroopAll,	// on all field excluding towers
		All,		// basically everywhere
	};

	inline PlacementType placementFromString(const std::string& str)
	{
		if (str == "troop")		return PlacementType::Troop;
		if (str == "troopall")	return PlacementType::TroopAll;
		if (str == "all")		return PlacementType::All;

		assert(false);
		throw new std::invalid_argument("PlacementType cannot be constructred from: " + str);
	}
}