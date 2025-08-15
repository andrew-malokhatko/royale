#pragma once

#include "Packet.hpp"
#include "cardPlacedEvent.hpp"

namespace Net
{
#pragma pack(push, 1)
	struct CardPlacedPacketData : public PacketData
	{
		double x{};
		double y{};
		royale::CardType card{};
	};
#pragma pack(pop)

	class CardPlacedPacket : public Packet
	{
		CardPlacedPacketData mData {};

	public:
		CardPlacedPacket(const royale::CardPlacedEvent& event);
		~CardPlacedPacket() = default;

		PacketType getType() const override;
		std::unique_ptr<royale::Event> getEvent() const;

		std::vector<uint8_t> pack() const override;
		static CardPlacedPacket unpack(const std::vector<uint8_t>& buffer);

	private:
		CardPlacedPacket() = default;
	};
}