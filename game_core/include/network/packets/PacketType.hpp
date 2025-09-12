#pragma once

#include <cstdint>

namespace Net
{
	namespace pack
	{
		static constexpr uint32_t OffsetMask =	0xfffffff0;
		static constexpr uint32_t GameOffset =	0x00000010;
		static constexpr uint32_t UIOffset =	0x00000100;
	}

	enum class PacketType : uint32_t
	{
		None = 0,	//	Invalid Packet

		// Game packets (16 max)
		CardPlacedPacket = pack::GameOffset,	//	Holds CardPlaced event

		// UI packets (16 max)
		LoginPacket = pack::UIOffset,	// Packet used to log in the user
		MatchmakingPacket				// Packet used to start or stop matchmaking
	};

	static bool isGamePacket(PacketType p)
	{
		return static_cast<uint32_t>(p) & pack::GameOffset;
	}

	static bool isUIPacket(PacketType p)
	{
		return static_cast<uint32_t>(p) & pack::UIOffset;
	}

	static uint32_t getPacketMask(PacketType p)
	{
		return static_cast<uint32_t>(p) & pack::OffsetMask;
	}
}