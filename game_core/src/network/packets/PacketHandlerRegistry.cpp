#include "PacketHandlerRegistry.hpp"
#include "CardPlacedPacketHandler.hpp"

namespace Net
{
	PacketHandlerRegistry::PacketHandlerRegistry()
	{
		handlers[PacketType::CardPlacedPacket] = new CardPlacedPacketHandler();
	}

	void PacketHandlerRegistry::handlePacket(const Packet* packet, Server& server)
	{
		PacketHandler* packetHandler = handlers[packet->getType()];
		packetHandler->handle(packet, server);
	}
}