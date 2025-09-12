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

		std::vector<std::unique_ptr<Net::GamePacket>> gamePackets;
		std::vector<std::unique_ptr<Net::Packet>> UIPackets;

		// sort packets
		for (auto& packet : packets)
		{
			uint32_t mask = getPacketMask(packet->getType());

			switch (mask)
			{
			case Net::pack::GameOffset:
				{
					auto* gp = static_cast<Net::GamePacket*>(packet.release());
					gamePackets.emplace_back(gp);
					break;
				}

			case Net::pack::UIOffset:
				UIPackets.emplace_back(std::move(packet));
				break;
			}
		}

		auto gameEvents = eventsFromPackets(gamePackets);
		mGame.processEvents(gameEvents);

		mView->processPackets(UIPackets);
		//
		// Process UI Packets
		//
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
