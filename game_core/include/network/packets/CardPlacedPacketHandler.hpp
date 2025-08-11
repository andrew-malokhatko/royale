#include "PacketHandler.hpp"

namespace Net
{
    class CardPlacedPacketHandler : public PacketHandler
    {
    public:
        void handle(const Packet* packet, Server& server) override;
    };
}