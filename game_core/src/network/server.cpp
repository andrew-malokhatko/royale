#include "server.hpp"


#include "NetUtils.hpp"
#include <thread>
#include <string>
#include <iostream>
#include <cassert>
#include <CardPlacedPacket.hpp>

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

			int clientSocket = accept(mServerSocket, clientSockAddr, &addrlen);
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
			const ClientInfo& clientInfo = clients[clientId];
			clientsMutex.unlock();

			SOCKET clientSocket = clientInfo.socket;
			std::vector<uint8_t> data(4096); // 4 Kib

			int bytesReceived = recv(clientSocket, reinterpret_cast<char*>(data.data()), data.size(), 0);
			if (bytesReceived <= 0)
			{
				continue;
			}

			auto packet = packetFromBytes(data);
			packetHandler.handlePacket(packet.get(), *this);
		}

		// Do not forget to join the thread after it has finished the execution
		clientsMutex.lock();
		assert(clientThreads.contains(clientId));
		clientThreads[clientId].join();
		clientsMutex.unlock();
	}

	void Server::sendPacket(client_id clientId, const Packet* packet)
	{
		clientsMutex.lock();
		SOCKET clientSocket = clients[clientId].socket;
		clientsMutex.unlock();

		std::vector<uint8_t> data = packet->pack();
		assert(!data.empty());

		send(clientSocket, reinterpret_cast<const char*>(data.data()), data.size(), 0);
	}

	void Server::broadcast(const Packet* packet)
	{
		clientsMutex.lock();
		for (const auto& clientPair : clients)
		{
			const ClientInfo& clientInfo = clientPair.second;
			sendPacket(clientInfo.id, packet);
		}
		clientsMutex.unlock();
	}
}