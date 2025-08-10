#pragma once

#include "Packet.hpp"
#include "server.hpp"

namespace Net
{
	class PacketHandler
	{
	public:
		//
		//	This function handles the specific packet
		//  It uses server to send responses to the packets or save some data
		//
		virtual void handle(const Packet* packet, Server& server) = 0;
	};
}