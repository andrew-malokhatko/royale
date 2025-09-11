#pragma once

#include <atomic>
#include "game.hpp"
#include "clock.hpp"
#include "View.hpp"
#include "client.hpp"

class Application
{
	const int WINDOW_WIDTH = 500;
	const int WINDOW_HEIGHT = 980;
	const char* WINDOW_TITLE = "Royale";

	royale::Clock mClock {};
	royale::Game mGame {};
	royale::View* mView {};

	Net::Client mClient{};

	bool multiplayer = false;
	std::atomic<bool> running = true;

	void intializeConnection();

public:
	Application();
	~Application();

	void update();
	void draw();
	bool isRunning();
};