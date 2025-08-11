#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <memory>
#include "Packet.hpp"
#include "event.hpp"

namespace Net
{
	class Client
	{
		int mSocket{};

		std::atomic<bool> mConnected{};
		std::thread mReceiveThread {};

		std::vector<std::unique_ptr<Packet>> incomingPackets{};
		std::mutex packetsMutex{};

	public:
		Client();
		~Client();

		void startConnection(int port = 3490);
		void endConnection();

		//void sendEvent(Event* event);
		void sendPacket(const Packet* packet);
		void receivePackets();
		std::vector<std::unique_ptr<Packet>> getIncomingPackets();

		bool isConnected();

		// SEPARATE CLASS
		void sendEvent(const royale::Event* event);
	};
}