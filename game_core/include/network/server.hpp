#pragma once

#include <unordered_map>
#include <mutex>
#include <atomic>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "PacketHandlerRegistry.hpp"

namespace Net
{
	class Server
	{
		using client_id = size_t;

		struct ClientInfo
		{
			client_id id;
			SOCKET socket;
			sockaddr_storage address;
		};

		static constexpr int BACKLOG = 10;	// Maximum number of pending connections

		int mServerSocket{};
		std::atomic<bool> mActive{};
		std::string mAddress{};
		client_id mClientIdCounter = 0;

		std::unordered_map<client_id, ClientInfo> clients;
		std::unordered_map<client_id, std::thread> clientThreads;
		std::mutex clientsMutex;

		PacketHandlerRegistry packetHandler{};

		void listenForClients();
		void handleClient(client_id clientId);
		void sendPacketSock(SOCKET socket, const Packet* packet) const;

	public:
		Server();
		~Server();

		void start(int port = 3490);
		void stop();
		bool isActive() const;

		void broadcast(const Packet* packet);
		void sendPacket(client_id clientId, const Packet* packet);
	};
}