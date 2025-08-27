#include "applicationView.hpp"
#include "GameScene.hpp"


ApplicationView::ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game)
	:
	mResolution{ resolutionX, resolutionY },
	mWindowTitle{ windowTitle }
{
	InitWindow(resolutionX, resolutionY, windowTitle);

	Rectangle resolutionRect = { 0, 0, mResolution.x, mResolution.y };
	mCurScene = std::make_unique<ui::GameScene>(resolutionRect, game);
}

void ApplicationView::resize(float x, float y, const royale::Game& game)
{
	mCurScene->resize(x, y);
}

void ApplicationView::render(const royale::Game& game)
{
	BeginDrawing();
	mCurScene->draw();
	EndDrawing();
}

void ApplicationView::update(const royale::Game& game)
{
	mCurScene->handleInput();
	mCurScene->update();
}

std::vector<std::unique_ptr<royale::Event>>	ApplicationView::pollEvents()
{
	return mCurScene->pollEvents();
}