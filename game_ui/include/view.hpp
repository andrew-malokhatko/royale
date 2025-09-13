#pragma once

#include "game.hpp"
#include "Packet.hpp"
#include <memory>

namespace royale
{
	class View
	{
	public:

		/*
		*  This function resizes the window to the width of "x" and height of "y".
		*/
		virtual void resize(float x, float y, const royale::Game& game) = 0;

		/*
		*  This function updates the View. It handles the input and generates events.
		*/
		virtual void update(const royale::Game& game) = 0;

		/*
		* This funciton draws a game.
		*/
		virtual void render(const Game& game) = 0;

		/*
		* This function returns events generated during the update function.
		*/
		virtual std::vector<std::unique_ptr<Event>> pollEvents() = 0;

		/*
		* This function updates the UI based on received packets
		*/
		virtual void processPackets(const std::vector<std::unique_ptr<net::Packet>>& packets) = 0;

		/*
		* This function starts watiting state (Usually a loading screen).
		*/
		virtual void startWaiting() = 0;

		/*
		* This function stops the waiting state (View behaves normally). 
		*/
		virtual void stopWaiting() = 0;
	};
}
