#pragma once

#include "Packet.hpp"

namespace Net
{
	enum MatchmakingEvent
	{
		START,
		STOP
	};

#pragma pack(push, 1)
	struct MatchamakingPacketData : public PacketData
	{
		MatchmakingEvent event;
	};
#pragma pack(pop)

	class MatchmakingPacket : public Packet
	{
		MatchamakingPacketData mData{};

	public:
		MatchmakingPacket(MatchmakingEvent event);
		~MatchmakingPacket() = default;

		PacketType getType() const override;

		std::vector<uint8_t> pack() const override;
		static MatchmakingPacket unpack(const std::vector<uint8_t>& buffer);

		MatchmakingEvent getEvent() const;

	private:
		MatchmakingPacket() = default;
	};
}