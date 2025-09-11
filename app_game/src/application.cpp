#include "application.hpp"
#include "ApplicationView.hpp"
#include "Utils.hpp"
#include <memory>

// block until the connection is established
void Application::intializeConnection()
{
	while (running && !mClient.isConnected())
	{
		mClient.startConnection();
		multiplayer = true;
	}
}

Application::Application()
{
	mView = new ApplicationView(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, mGame, mClient);
	mView->startWaiting();	// display a loading screen until everything is unitalized

	mClock.startClock();
	std::thread([this]() {
		intializeConnection();
		mView->stopWaiting();	// restore the scene after the connection was established
	}).detach();
}

Application::~Application()
{
	CloseWindow();
	running = false;
}

void Application::update()
{
	if (WindowShouldClose())
		running = false;

	mView->update(mGame);

	if (!running || !mClient.isConnected())
		return;

	// delta time seconds
	double dt = mClock.getTimeSinceLastCall();

	mGame.update(dt);

	///
	/// EXRACT THIS LOGIC TO SEPARAE FILE
	/// 
	auto clientEvents = mView->pollEvents();

	if (multiplayer)
	{
		// send generated events to the server for validation etc.
		for (const auto& event : clientEvents)
		{
			mClient.sendEvent(event.get());
		}

		// receive packets from yourself and other clients
		auto packets = mClient.getIncomingPackets();
		auto events = eventsFromPackets(packets);

		mGame.processEvents(events);
	}
	else
	{
		mGame.processEvents(clientEvents);
	}
}

void Application::draw()
{
	mView->render(mGame);
}

bool Application::isRunning()
{
	return running;
}
