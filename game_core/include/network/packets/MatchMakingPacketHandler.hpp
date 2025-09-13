#include "PacketHandler.hpp"

namespace net
{
    class MatchmakingPacketHandler : public PacketHandler
    {
    public:
        void handle(const Packet* packet, Server& server, ClientInfo& clientInfo) override;
    };
}