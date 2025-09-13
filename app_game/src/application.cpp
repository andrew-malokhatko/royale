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

	if (running && mClient.isConnected())
	{ 
		// delta time seconds
		double dt = mClock.getTimeSinceLastCall();
		mGame.update(dt);

		///
		/// EXRACT THIS LOGIC TO SEPARAE FILE
		/// 
		auto clientEvents = mView->pollEvents();
		for (const auto& event : clientEvents)
		{
			mClient.sendEvent(event.get());
		}

		auto packets = mClient.getIncomingPackets();
		std::vector<std::unique_ptr<net::GamePacket>> gamePackets;
		std::vector<std::unique_ptr<net::Packet>> UIPackets;

		// sort packets
		for (auto& packet : packets)
		{
			uint32_t mask = getPacketMask(packet->getType());

			switch (mask)
			{
			case net::pack::GameOffset:
			{
				auto* gp = static_cast<net::GamePacket*>(packet.release());
				gamePackets.emplace_back(gp);
				break;
			}

			case net::pack::UIOffset:
				UIPackets.emplace_back(std::move(packet));
				break;
			}
		}

		auto gameEvents = eventsFromPackets(gamePackets);
		mGame.processEvents(gameEvents);

		mView->processPackets(UIPackets);
	}

	mView->update(mGame);
}

void Application::draw()
{
	mView->render(mGame);
}

bool Application::isRunning()
{
	return running;
}
