#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>

namespace royale
{
	enum class TargetType
	{
		Ground,
		Air,
		Buildings,
		Any,
	};

	inline TargetType targetFromString(const std::string& str)
	{
		if (str == "ground")		return TargetType::Ground;
		if (str == "air")			return TargetType::Air;
		if (str == "buildings")		return TargetType::Buildings;
		if (str == "any")			return TargetType::Any;

		throw std::invalid_argument("Invalid TargetType string: " + str);
	}
}