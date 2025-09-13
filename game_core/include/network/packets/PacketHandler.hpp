#pragma once

#include "Packet.hpp"

namespace net
{
	// Predefinition of server class
	// this way packet handler can store unique instructions for the 
	// server to execute for the packet
	class Server;
	struct ClientInfo;

	class PacketHandler
	{
	public:
		//
		//	This function handles the specific packet
		//
		virtual void handle(const Packet* packet, Server& server, ClientInfo& clientInfo) = 0;
	};
}