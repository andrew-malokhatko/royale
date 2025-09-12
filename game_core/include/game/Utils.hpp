#pragma once

#include "GamePacket.hpp"

std::vector<std::unique_ptr<Net::Packet>> packetsFromEvents(const std::vector<std::unique_ptr<royale::Event>>& events)
{
	std::vector<std::unique_ptr<Net::Packet>> packets{};
	packets.reserve(events.size());

	for (const auto& event : events)
	{
		packets.emplace_back(event->getPacket());
	}

	return packets;
}

std::vector<std::unique_ptr<royale::Event>> eventsFromPackets(const std::vector<std::unique_ptr<Net::GamePacket>>& packets)
{
	std::vector<std::unique_ptr<royale::Event>> events{};
	events.reserve(packets.size());

	for (const auto& packet : packets)
	{
		events.emplace_back(packet->getEvent());
	}

	return events;
}