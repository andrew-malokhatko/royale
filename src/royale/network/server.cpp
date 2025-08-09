#include "server.hpp"


#include "NetUtils.hpp"
#include <thread>
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>


namespace Net
{
	Server::Server()
	{
		initWSA();
	}

	Server::~Server()
	{
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
		std::string mAddress = getAddress(addrInfo);
		std::cout << "Succesfully bound to " << mAddress << "\n";
		freeaddrinfo(res);

		// start listening
		std::thread listenThread(&Server::listenForClients, this);
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

		while (mActive)
		{
			sockaddr_storage clientSockAddrStorage;

			sockaddr* clientSockAddr = reinterpret_cast<sockaddr*>(&clientSockAddrStorage);
			int addrlen = sizeof(clientSockAddrStorage);
			int clientSocket = accept(mServerSocket, (sockaddr*)clientSockAddr, &addrlen);

			if (clientSocket == -1)
			{
				std::cout << "Client was not accepted\n";
				continue;
			}

			ClientInfo clientInfo = {++mClientIdCounter, clientSocket, clientSockAddrStorage};
			clientsMutex.lock();
			clients[clientSocket] = clientInfo;
			clientsMutex.unlock();

			std::string clientAddress = getAddress(clientSockAddr);
			std::string clientIPver = getIPVersion(clientSockAddr);
			std::cout << "Client connected with: " << clientIPver << " " << clientAddress << "\n";

			std::thread clientThread(&Server::handleClient, this, clientInfo.id);
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

		clientsMutex.unlock();
	}

	bool Server::isActive()
	{
		return mActive;
	}

	void Server::handleClient(client_id clientId)
	{
		// recieve data from client
		// ...
		// ...
		// ...
		// ...
	}

	void Server::sendPacket(client_id clientId, int packetId)
	{
		// send data to client with clientId
		// ...
		// ...
		// ...
		// ...
	}
}