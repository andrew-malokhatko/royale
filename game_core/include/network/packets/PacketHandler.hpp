#pragma once

#include "Packet.hpp"

namespace Net
{
	// Predefinition of server class
	// this way packet handler can store unique instructions for the 
	// server to execute for the packet
	class Server;

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