#include "application.hpp"
#include "ApplicationView.hpp"
#include "Utils.hpp"
#include <memory>

Application::Application()
{
	mView = new ApplicationView(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, mGame, mClient);
	mClock.startClock();
	mClient.startConnection();
}

Application::~Application()
{
	CloseWindow();
} 

void Application::update()
{
	// delta time seconds
	double dt = mClock.getTimeSinceLastCall();

	mGame.update(dt);
	mView->update(mGame);


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

	if (WindowShouldClose())
	{
		running = false;
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
