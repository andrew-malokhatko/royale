#pragma once

#include "Packet.hpp"

namespace net
{
	class GamePacket : public Packet
	{
	public:

		virtual ~GamePacket() = default;
		virtual std::unique_ptr<royale::Event> getEvent() const = 0;
	};
}