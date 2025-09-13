#include "MatchmakingPacket.hpp"
#include <cassert>

namespace net
{
	MatchmakingPacket::MatchmakingPacket(MatchmakingEvent event)
	{
		mData.packetType = PacketType::MatchmakingPacket;
		mData.event = event;
	}

	PacketType MatchmakingPacket::getType() const
	{
		assert(mData.packetType == PacketType::MatchmakingPacket);
		return mData.packetType;
	}

	std::vector<uint8_t> MatchmakingPacket::pack() const
	{
		int dataSize = sizeof MatchamakingPacketData;
		std::vector<uint8_t> buf(dataSize);
		std::memcpy(buf.data(), &mData, dataSize);
		return buf;
	}

	MatchmakingPacket MatchmakingPacket::unpack(const std::vector<uint8_t>& buf)
	{
		int dataSize = sizeof MatchamakingPacketData;
		assert(dataSize == buf.size());
		MatchmakingPacket packet{};
		std::memcpy(&packet.mData, buf.data(), dataSize);
		return packet;
	}

	MatchmakingEvent MatchmakingPacket::getEvent() const
	{
		return mData.event;
	}
}