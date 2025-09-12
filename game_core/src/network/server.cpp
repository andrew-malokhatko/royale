#include "server.hpp"

#include "NetUtils.hpp"
#include <thread>
#include <string>
#include <iostream>
#include <cassert>
#include "CardPlacedPacket.hpp"
#include "MatchmakingPacket.hpp"

namespace Net
{
	Server::Server()
	{
		initWSA();
	}

	Server::~Server()
	{
		stop();
		WSACleanup();
	}

	void Server::start(int port)
	{
		addrinfo hints {};
		addrinfo* res = nullptr;
		std::string portStr = std::to_string(port);

		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE;

		int addressInfoStatus = getaddrinfo(NULL, portStr.c_str(), &hints, &res);
		if (addressInfoStatus != 0)
		{
			std::cerr << "getaddressinfo() error: " << gai_strerror(addressInfoStatus) << ".\n";
			return;
		}
		std::cout << "Address info retrieved succesfully.\n";

		addrinfo* p;
		for (p = res; p != nullptr; p = p->ai_next)
		{
			mServerSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
			if (mServerSocket == -1)
			{
				std::cerr << "Could not initialize server socket.\n";
				continue;
			}

			char yes = 1;
			int sockOptSuc = setsockopt(mServerSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
			if (sockOptSuc == -1)
			{
				std::cerr << "Could not set SO_REUSEADDR socket option to true.\n";
				continue;
			}

			int sockBindSuc = bind(mServerSocket, p->ai_addr, p->ai_addrlen);
			if (sockBindSuc == -1)
			{
				std::cerr << "Could not bind the socket\n";
				continue;
			}

			break;
		}

		// if server socket was not initialized throw an error
		if (p == NULL)
		{
			std::cerr << "Socket was not initiaize or successfully bound. End of server.start().\n";
			return;
		}

		addrinfo* addrInfo = p;
		mAddress = getAddress(addrInfo);
		std::cout << "Succesfully bound to " << mAddress << "\n";
		freeaddrinfo(res);

		// start listening
		std::thread listenThread(&Server::listenForClients, this);
		listenThread.join();
	}

	void Server::listenForClients()
	{
		int sockListenSuc = listen(mServerSocket, BACKLOG);
		if (sockListenSuc == -1)
		{
			std::cerr << "Could not start listening on the given socket. Exiting....\n";
			exit(1);
		}

		mActive = true;
		std::cout << "Listening on: " << mAddress << "\n";

		while (isActive())
		{
			sockaddr_storage clientSockAddrStorage{};
			sockaddr* clientSockAddr = reinterpret_cast<sockaddr*>(&clientSockAddrStorage);
			socklen_t addrlen = sizeof(clientSockAddrStorage);

			SOCKET clientSocket = accept(mServerSocket, clientSockAddr, &addrlen);
			if (clientSocket == -1)
			{
				std::cout << "Client was not accepted\n";
				continue;
			}

			std::string clientAddress = getAddress(clientSockAddr);
			std::string clientIPver = getIPVersion(clientSockAddr);
			std::cout << "Client connected with: " << clientIPver << " " << clientAddress << "\n";

			client_id clientId = ++mClientIdCounter;
			ClientInfo clientInfo = { clientId, clientSocket, clientSockAddrStorage};

			clientsMutex.lock();
			clients[clientId] = clientInfo;
			clientThreads[clientId] = std::thread(&Server::handleClient, this, clientId);
			clientsMutex.unlock();
		}
	}

	void Server::stop()
	{
		mActive = false;

		clientsMutex.lock();

		for (auto clientPair : clients)
		{
			ClientInfo& clientInfo = clientPair.second;
			closesocket(clientInfo.id);
		}
		clients.clear();

		for (auto& clientPair : clientThreads)
		{
			std::thread& clientThread = clientPair.second;
			clientThread.join();
		}
		clientThreads.clear();

		clientsMutex.unlock();
	}

	bool Server::isActive() const
	{
		return mActive.load();
	}

	void Server::handleClient(client_id clientId)
	{
		while (isActive())
		{
			clientsMutex.lock();
			ClientInfo& clientInfo = clients[clientId];
			SOCKET clientSocket = clientInfo.socket;
			clientsMutex.unlock();

			std::vector<uint8_t> data(4096); // 4 Kib

			int bytesReceived = recv(clientSocket, reinterpret_cast<char*>(data.data()), data.size(), 0);
			if (bytesReceived <= 0)
			{
				continue;
			}
			data.resize(bytesReceived);

			std::lock_guard lock(clientsMutex);
			auto packet = packetFromBytes(data);
			packetHandler.handlePacket(packet.get(), *this, clientInfo);
		}

		// Do not forget to join the thread after it has finished the execution
		clientsMutex.lock();
		assert(clientThreads.contains(clientId));
		clientThreads[clientId].join();
		clientsMutex.unlock();
	}

	void Server::sendPacketSock(SOCKET socket, const Packet* packet) const
	{
		std::vector<uint8_t> data = packet->pack();
		assert(!data.empty());

		send(socket, reinterpret_cast<const char*>(data.data()), data.size(), 0);
	}

	void Server::sendPacket(client_id clientId, const Packet* packet)
	{	
		clientsMutex.lock();
		SOCKET clientSocket = clients[clientId].socket;
		clientsMutex.unlock();

		sendPacketSock(clientSocket, packet);
	}

	void Server::broadcast(const Packet* packet)
	{
		std::vector<SOCKET> clientSockets(clients.size());

		// first gather the sockets and only then send data
		// this avoids long blocking that IO operations have
		{
			std::lock_guard lock(clientsMutex);
			for (const auto& [id, clientInfo] : clients)
			{
				clientSockets.push_back(clientInfo.socket);
			}
		}
		
		// Now send all of the packets without locking clients
		for (auto socket : clientSockets)
		{
			sendPacketSock(socket, packet);
		}
	}

	void Server::findGame(client_id clientId)
	{
		std::lock_guard lock(clientsMutex);

		assert(clients.contains(clientId));
		queuedClients.insert(clientId);

		if (queuedClients.size() >= 2)
		{
			auto matchPacket = std::make_unique<MatchmakingPacket>(MatchmakingEvent::START);

			client_id player1 = *(queuedClients.begin());
			client_id player2 = *(++queuedClients.begin());

			sendPacket(player1, matchPacket.get());
			sendPacket(player2, matchPacket.get());
		}
	}

	void Server::stopFindGame(client_id clientId)
	{
		std::lock_guard lock(clientsMutex);

		queuedClients.erase(clientId);

		//auto matchPacket = std::make_unique<MatchmakingPacket>(MatchmakingEvent::STOP);
		//sendPacket(clientId, matchPacket.get());
	}
}