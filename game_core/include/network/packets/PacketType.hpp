#pragma once

#include <cstdint>

namespace Net
{
	enum class PacketType : uint8_t
	{

		//
		//	Invalid Packet
		//
		None,

		// 
		// Packet used to log in the user
		//
		LoginPacket,

		//
		//	Packet used to start matchmaking
		//
		FindGamePacket,

		//
		//	Holds CardPlaced event
		//
		CardPlacedPacket
	};
}