#include "CardPlacedPacketHandler.hpp"

#include "CardPlacedPacket.hpp"
#include "server.hpp"
#include <cassert>

namespace Net
{
	
	void CardPlacedPacketHandler::handle(const Packet* packet, Server& server)
	{
		// This is how you could cast the packet
		// to process it on the server
		const CardPlacedPacket* cardPacket = static_cast<const CardPlacedPacket*>(packet);

		server.broadcast(packet);
	}
}