#pragma once

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>
#include "packet.hpp"
#include "event.hpp"

namespace Net
{
	void initWSA();

	std::string getAddress(const sockaddr* sockAddr);
	std::string getAddress(const addrinfo* addrInfo);

	std::string getIPVersion(addrinfo* addrInfo);
	std::string getIPVersion(sockaddr* sockAddr);

	std::unique_ptr<Packet> packetFromBytes(const std::vector<uint8_t>& bytes);
}