#include "PacketHandlerRegistry.hpp"
#include "CardPlacedPacketHandler.hpp"

namespace Net
{
	PacketHandlerRegistry::PacketHandlerRegistry()
	{
		handlers[PacketType::CardPlacedPacket] = new CardPlacedPacketHandler();
	}

	PacketHandlerRegistry::~PacketHandlerRegistry()
	{
		for (auto pair : handlers)
		{
			auto handler = pair.second;
			delete handler;
		}
		handlers.clear();
	}

	void PacketHandlerRegistry::handlePacket(const Packet* packet, Server& server)
	{
		PacketHandler* packetHandler = handlers[packet->getType()];
		packetHandler->handle(packet, server);
	}
}