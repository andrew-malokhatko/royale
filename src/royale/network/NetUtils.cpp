#include "NetUtils.hpp"

#include <iostream>

namespace Net
{
	void initWSA()
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			WSACleanup();
			std::cerr << "WSA could not start up.\n";
			std::cerr << "Exiting...\n";

			exit(1);
		}
	}

	std::string getAddress(const sockaddr* sockAddr)
	{
		if (!sockAddr)
		{
			return std::string{};
		}

		char buffer[INET6_ADDRSTRLEN] = {};

		if (sockAddr->sa_family == AF_INET)
		{
			const sockaddr_in* sockAddr4 = reinterpret_cast<const sockaddr_in*>(sockAddr);
			const in_addr address = sockAddr4->sin_addr;
			inet_ntop(AF_INET, &address, buffer, sizeof(buffer));
		}
		else if (sockAddr->sa_family == AF_INET6)
		{
			const sockaddr_in6* sockAddr6 = reinterpret_cast<const sockaddr_in6*>(sockAddr);
			const in6_addr address = sockAddr6->sin6_addr;
			inet_ntop(AF_INET6, &address, buffer, sizeof(buffer));
		}
		else
		{
			std::cout << "Unsupported address family\n";
			return std::string{};
		}

		return std::string(buffer);
	}

	std::string getAddress(const addrinfo* addrInfo)
	{
		if (!addrInfo)
		{
			return std::string{};
		}

		return getAddress(addrInfo->ai_addr);
	}

	std::string getIPVersion(addrinfo* addrInfo)
	{
		return addrInfo->ai_family == AF_INET ? "IPv4" : "IPv6";
	}

	std::string getIPVersion(sockaddr* sockAddr)
	{
		return sockAddr->sa_family == AF_INET ? "IPv4" : "IPv6";
	}
}