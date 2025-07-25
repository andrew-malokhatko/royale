#pragma once

#include "game.hpp"
#include "clock.hpp"
#include "view.hpp"

class Application
{
	const int WINDOW_WIDTH = 500;
	const int WINDOW_HEIGHT = 980;
	const char* WINDOW_TITLE = "Royale";

	royale::Clock mClock {};
	royale::Game mGame {};
	royale::View* mView;

	bool running = true;

public:
	Application();
	~Application();

	void update();
	void draw();
	bool isRunning();
};