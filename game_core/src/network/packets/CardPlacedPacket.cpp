#include "CardPlacedPacket.hpp"
#include <cassert>

namespace net
{
	CardPlacedPacket::CardPlacedPacket(const royale::CardPlacedEvent& event)
	{
		royale::Vector2 pos = event.getPosition();

		mData.packetType = PacketType::CardPlacedPacket;
		mData.x = pos.x;
		mData.y = pos.y;
		mData.card = event.getCard();
	}

	PacketType CardPlacedPacket::getType() const
	{
		assert(mData.packetType == PacketType::CardPlacedPacket);
		return mData.packetType;
	}

	std::vector<uint8_t> CardPlacedPacket::pack() const
	{
		int dataSize = sizeof CardPlacedPacketData;
		std::vector<uint8_t> buf(dataSize);
		std::memcpy(buf.data(), &mData, dataSize);
		return buf;
	}

	CardPlacedPacket CardPlacedPacket::unpack(const std::vector<uint8_t>& buf)
	{
		int dataSize = sizeof CardPlacedPacketData;
		assert(dataSize == buf.size());
		CardPlacedPacket packet {};
		std::memcpy(&packet.mData, buf.data(), dataSize);
		return packet;
	}

	std::unique_ptr<royale::Event> CardPlacedPacket::getEvent() const
	{
		return std::make_unique<royale::CardPlacedEvent>(royale::Vector2{mData.x, mData.y}, mData.card);
	}
}