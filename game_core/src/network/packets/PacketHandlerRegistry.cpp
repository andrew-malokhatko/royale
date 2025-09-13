#include "PacketHandlerRegistry.hpp"
#include "CardPlacedPacketHandler.hpp"
#include "MatchmakingPacketHandler.hpp"

namespace net
{
	PacketHandlerRegistry::PacketHandlerRegistry()
	{
		handlers[PacketType::CardPlacedPacket] = new CardPlacedPacketHandler();
		handlers[PacketType::MatchmakingPacket] = new MatchmakingPacketHandler();
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

	void PacketHandlerRegistry::handlePacket(const Packet* packet, Server& server, ClientInfo& clientInfo)
	{
		PacketHandler* packetHandler = handlers[packet->getType()];
		packetHandler->handle(packet, server, clientInfo);
	}
}