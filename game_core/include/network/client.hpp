#pragma once

#include <thread>

namespace Net
{
	class Client
	{
		int mSocket{};
		bool mConnected{};

		std::thread mReceiveThread {};

	public:
		Client();
		~Client();

		void startConnection(int port = 3490);
		void endConnection();

		//void sendEvent(Event* event);
		void sendPacket(int packetId);
		void receivePacket();

		bool isConnected();
	};
}