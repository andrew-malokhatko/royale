#include "PacketHandler.hpp"

namespace net
{
    class CardPlacedPacketHandler : public PacketHandler
    {
    public:
        void handle(const Packet* packet, Server& server, ClientInfo& clientInfo) override;
    };
}