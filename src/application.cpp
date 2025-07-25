#include "application.hpp"
#include "applicationView.hpp"

Application::Application()
{
	mView = new ApplicationView(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, mGame);
	mClock.startClock();
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
	std::vector<royale::Event*> events = mView->pollEvents();
	mGame.processEvents(events);

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
