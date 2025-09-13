#pragma once

#include <winsock2.h>

namespace net
{
	using client_id = size_t;

	enum ClientState
	{
		Idle,
		Matchmaking,
		Game
	};

	struct ClientInfo
	{
		client_id id;
		SOCKET socket;
		sockaddr_storage address;
		ClientState state;
	};
}
