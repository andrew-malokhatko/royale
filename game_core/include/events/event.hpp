#pragma once

#include "EventType.hpp"
#include "Packet.hpp"

namespace royale
{
	// Forward declaration of a Game class
	// to avoid circular dependency
	class Game;

	class Event
	{
	protected:
		EventType mEventType;

	public:

		Event(EventType eventType)
		{
			mEventType = eventType;
		}

		virtual ~Event() = default;

		// Each event can be applied to a game 
		virtual void apply(Game& game) = 0;
		virtual std::unique_ptr<net::Packet> getPacket() const = 0;

		EventType getEventType() const
		{
			return mEventType;
		}
	};
}
