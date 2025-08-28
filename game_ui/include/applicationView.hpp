#pragma once

#include "View.hpp"
#include "Scene.hpp"
#include <memory>
#include <vector>
#include <unordered_map>


class ApplicationView : public royale::View
{
	Vector2 mResolution;
	const char* mWindowTitle;

	std::unique_ptr<ui::Scene> mCurScene;
	std::unordered_map<ui::NodeId, std::unique_ptr<ui::Scene>> mScenes{};

public:
	ApplicationView(float resolutionX, float resolutionY, const char* windowTitle, const royale::Game& game);

	void resize(float x, float y, const royale::Game& game) override;
	void update(const royale::Game& game) override;
	void render(const royale::Game& game) override;
	std::vector<std::unique_ptr<royale::Event>> pollEvents() override;
};
