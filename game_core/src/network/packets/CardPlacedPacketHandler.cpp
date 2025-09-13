#include "CardPlacedPacketHandler.hpp"

#include "CardPlacedPacket.hpp"
#include "server.hpp"
#include <cassert>

namespace net
{
	
	void CardPlacedPacketHandler::handle(const Packet* packet, Server& server, ClientInfo& clientInfo)
	{
		const CardPlacedPacket* cardPacket = static_cast<const CardPlacedPacket*>(packet);

		server.broadcast(packet);
	}
}