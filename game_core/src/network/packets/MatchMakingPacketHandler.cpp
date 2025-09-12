#include "MatchmakingPacketHandler.hpp"

#include "MatchmakingPacket.hpp"
#include "server.hpp"
#include <cassert>

namespace Net
{
	
	void MatchmakingPacketHandler::handle(const Packet* packet, Server& server, ClientInfo& clientInfo)
	{
		const MatchmakingPacket* matchPacket = static_cast<const MatchmakingPacket*>(packet);
		auto matchEvent = matchPacket->getEvent();

		//clientInfo.state == ClientState::Idle &&
		//clientInfo.state == ClientState::Matchmaking && 

		if (matchEvent == MatchmakingEvent::START)
		{
			server.findGame(clientInfo.id);
		}

		if (matchEvent == MatchmakingEvent::STOP)
		{
			server.stopFindGame(clientInfo.id);
		}
	}
}