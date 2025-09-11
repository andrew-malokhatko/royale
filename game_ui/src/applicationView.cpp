#include "ApplicationView.hpp"
#include "GameScene.hpp"
#include "MainScene.hpp"
#include "SearchScene.hpp"
#include "LoadingScene.hpp"
#include <cassert>
#include <future>

ApplicationView::ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game, Net::Client& client)
	:
	mResolution{ resolutionX, resolutionY },
	mWindowTitle{ windowTitle }
{
	InitWindow(resolutionX, resolutionY, windowTitle);
	SetTargetFPS(60);	// do not melt the processor

	Rectangle resolutionRect = { 0, 0, mResolution.x, mResolution.y };

	loadScene("loading", std::make_shared<ui::LoadingScene>(resolutionRect, *this));

	loadingScene = "loading";
	nextScene = "main";
	
	//loadedAllScenes = std::async(std::launch::async, [this, resolutionRect, &game, &client]() {
		loadScene("main", std::make_shared<ui::MainScene>(resolutionRect, *this));
		loadScene("game", std::make_shared<ui::GameScene>(resolutionRect, *this, game));
		loadScene("search", std::make_shared<ui::SearchScene>(resolutionRect, client, *this));
		//return true;
	//});
}

void ApplicationView::loadScene(const std::string& name, std::shared_ptr<ui::Scene> scene)
{
	mScenes[name] = scene;
}

void ApplicationView::setScene(const std::string& name)
{
	if (mCurSceneName == name)
		return;

	std::lock_guard<std::mutex> lock(drawMutex);

	if (mCurScene)
		mCurScene->onSceneLeave();

	assert(mScenes.contains(name));
	mCurScene = mScenes.at(name);
	mCurSceneName = name;

	mCurScene->onSceneLoad();
}

void ApplicationView::resize(float x, float y, const royale::Game& game)
{
	mCurScene->resize(x, y);
}

void ApplicationView::render(const royale::Game& game)
{
	std::lock_guard lock(drawMutex);

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

void ApplicationView::startWaiting()
{
	//nextScene = mCurSceneName;	// save the current scene
	setScene(loadingScene);
}

void ApplicationView::stopWaiting()
{
	//loadedAllScenes.get();
	setScene(nextScene);	// restore current theme
}