#include "client.hpp"

#include "NetUtils.hpp"
#include "MatchmakingPacket.hpp"
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <cassert>

namespace Net
{
	Client::Client()
	{
		initWSA();
	}

	Client::~Client()
	{
		endConnection();
		WSACleanup();
	}

	void Client::startConnection(int port)
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
				std::cerr << "Connection Failed" << "\n";
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

		mConnected = true;
		mReceiveThread = std::thread(&Client::receivePackets, this);
	}

	void Client::endConnection()
	{
		if (mConnected && mReceiveThread.joinable())
		{
			mReceiveThread.join();
		}

		mConnected = false;
		closesocket(mSocket);
	}

	void Client::sendPacket(const Packet* packet)
	{
		std::vector<uint8_t> data = packet->pack();
		assert(!data.empty());

		send(mSocket, reinterpret_cast<const char*>(data.data()), data.size(), 0);
	}

	void Client::receivePackets()
	{
		while (isConnected())
		{
			std::vector<uint8_t> data(4096);

			int bytesReceived = recv(mSocket, reinterpret_cast<char*>(data.data()), data.size(), 0);
			if (bytesReceived <= 0)
			{
				continue;
			}
			data.resize(bytesReceived);

			auto packet = packetFromBytes(data);

			packetsMutex.lock();
			incomingPackets.push_back(std::move(packet));
			packetsMutex.unlock();
		}
	}

	std::vector<std::unique_ptr<Packet>> Client::getIncomingPackets()
	{
		std::lock_guard<std::mutex> lock(packetsMutex);
		return std::move(incomingPackets);
	}

	bool Client::isConnected() const
	{
		return mConnected.load();
	}

	void Client::sendEvent(const royale::Event* event)
	{
		auto packet = event->getPacket();

		sendPacket(packet.get());
	}

	void Client::findMatch()
	{
		auto matchPacket = std::make_unique<MatchmakingPacket>(MatchmakingEvent::START);
		sendPacket(matchPacket.get());
	}

	void Client::stopFindMatch()
	{
		auto matchPacket = std::make_unique<MatchmakingPacket>(MatchmakingEvent::STOP);
		sendPacket(matchPacket.get());
	}
}