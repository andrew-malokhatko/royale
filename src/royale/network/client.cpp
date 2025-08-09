#include "client.hpp"

#include "NetUtils.hpp"
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>

namespace Net
{
	Client::Client()
	{
	}

	Client::~Client()
	{
	}

	void Client::startConnection(int port = 3490)
	{
		addrinfo hints{};
		addrinfo* res = nullptr;
		std::string portStr = std::to_string(port);

		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE;

		int addressInfoStatus = getaddrinfo("localhost", portStr.c_str(), &hints, &res);
		if (addressInfoStatus != 0)
		{
			std::cerr << "getaddressinfo() error: " << gai_strerror(addressInfoStatus) << ".\n";
			return;
		}
		std::cout << "Address info retrieved succesfully.\n";

		addrinfo* p;
		for (p = res; p != nullptr; p = p->ai_next)
		{
			mSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
			if (mSocket == -1)
			{
				std::cerr << "Could not initialize server socket.\n";
				continue;
			}

			std::string address = getAddress(p);
			std::string ipVer = getIPVersion(p);
			std::cout << "Trying to connect to: " << ipVer << " " << address << "\n";

			int sockConnectSuc = connect(mSocket, p->ai_addr, p->ai_addrlen);
			if (sockConnectSuc == -1)
			{
				std::cerr << "Could not connect to socket" << address << "\n";
				continue;
			}

			std::cout << "Successfully connected to: " << address << "\n";
			break;
		}

		freeaddrinfo(res);

		// if server socket was not initialized throw an error
		if (p == NULL)
		{
			std::cerr << "Socket was not initiaize or could not connect. End of client.startConnection().\n";
			return;
		}

		std::thread receiveThread(&Client::receivePacket, this);

	}

	void Client::endConnection()
	{
		mConnected = false;
		closesocket(mSocket);
	}

	void Client::sendPacket(int packetId)
	{
		// send packets to the server
		//  ...
		// 	...
		// 	...
		//	...
	}

	int Client::receivePacket()
	{
		// receive and deserialize packets from the server
		//  ...
		// 	...
		// 	...
		//	...
	}

	bool Client::isConnected()
	{
		return mConnected;
	}
}