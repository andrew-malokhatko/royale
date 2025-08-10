#pragma once

#include "PacketType.hpp"

#include <vector>

namespace Net
{

#pragma pack(push, 1)
	struct PacketData
	{
		PacketType packetType;
	};
#pragma pack(pop)

	class Packet
	{
	public:

		virtual ~Packet() = default;
		virtual std::vector<uint8_t> pack() const = 0;
		virtual PacketType getType() const = 0;
	};
}