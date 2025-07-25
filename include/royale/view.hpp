#pragma once

#include "game.hpp"

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
		virtual std::vector<Event*> pollEvents() = 0;

	};
}
