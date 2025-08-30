#include "ApplicationView.hpp"
#include "GameScene.hpp"
#include "MainScene.hpp"
#include <cassert>


ApplicationView::ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game)
	:
	mResolution{ resolutionX, resolutionY },
	mWindowTitle{ windowTitle }
{
	InitWindow(resolutionX, resolutionY, windowTitle);

	Rectangle resolutionRect = { 0, 0, mResolution.x, mResolution.y };

	loadScene("main", std::make_shared<ui::MainScene>(resolutionRect, *this));
	loadScene("game", std::make_shared<ui::GameScene>(resolutionRect, *this, game));

	//mCurScene = std::make_unique<ui::GameScene>(resolutionRect, game);
	//mCurScene = std::make_unique<ui::MainScene>(resolutionRect);

	setScene("main");
}

void ApplicationView::loadScene(const std::string& name, std::shared_ptr<ui::Scene> scene)
{
	mScenes[name] = scene;
}

void ApplicationView::setScene(const std::string& name)
{
	mCurScene->onSceneLeave();

	assert(mScenes.contains(name));
	mCurScene = mScenes.at(name);

	mCurScene->onSceneLoad();
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