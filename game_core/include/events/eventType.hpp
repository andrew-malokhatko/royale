#pragma once

#include <cstdint>

namespace royale
{
	enum class EventType : uint8_t
	{
		CardPlaced,
		AbilityActivated
	};
}