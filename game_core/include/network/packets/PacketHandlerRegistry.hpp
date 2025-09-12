#pragma once

#include <unordered_map>
#include "PacketHandler.hpp"

namespace Net
{
	class PacketHandlerRegistry
	{
		std::unordered_map<PacketType, PacketHandler*> handlers{};

	public:
		PacketHandlerRegistry();
		~PacketHandlerRegistry();

		//
		// This function matches handlers with corresponding packet types
		//
		void handlePacket(const Packet* packet, Server& server, ClientInfo& clientInfo);
	};
}