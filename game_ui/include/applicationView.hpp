#pragma once

#include "View.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "client.hpp"
#include <memory>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <future>


class ApplicationView : public royale::View, public ui::SceneManager
{
	Vector2 mResolution;
	const char* mWindowTitle;

	std::shared_ptr<ui::Scene> mCurScene;
	std::unordered_map<std::string, std::shared_ptr<ui::Scene>> mScenes{};

	std::string mCurSceneName;
	std::string loadingScene {};
	std::string nextScene {};
	
	// prevent setScene while drawing
	std::mutex drawMutex {};
	//std::shared_future<bool> loadedAllScenes{};

private:
	void loadScene(const std::string& name, std::shared_ptr<ui::Scene> scene);

public:
	ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game, Net::Client& client);

	//API for ui::SceneManager
	void setScene(const std::string& name) override;

	// API for royale::View
	void resize(float x, float y, const royale::Game& game) override;
	void update(const royale::Game& game) override;
	void render(const royale::Game& game) override;
	std::vector<std::unique_ptr<royale::Event>> pollEvents() override;
	void startWaiting() override;
	void stopWaiting() override;
};
