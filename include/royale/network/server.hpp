#pragma once

#include <unordered_map>
#include <mutex>

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
		bool mActive{};
		std::string mAddress{};
		client_id mClientIdCounter = 0;

		std::unordered_map<client_id, ClientInfo> clients;
		std::mutex clientsMutex;


		//std::vector<int> data;
		//royale::Game game;

		void listenForClients();
		void handleClient(client_id clientId);
		void sendPacket(client_id clientId, int packetId);

	public:
		Server();
		~Server();

		void start(int port = 3490);
		void stop();
		bool isActive();
	};
}