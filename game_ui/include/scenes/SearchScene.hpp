#pragma once

#include "Scene.hpp"
#include "client.hpp"
#include "components/Button.hpp"
#include "components/LoadingIcon.hpp"

namespace ui
{
	class SearchScene : public Scene
	{
		net::Client& mClient;

		Button mStopSearchButton;
		LoadingIcon mLoadingIcon;
		TextureComponent mBackground;

	private:
		void stopSearch();

	public:
		SearchScene(Rectangle rectangle, net::Client& client, SceneManager& sceneManager);

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;

		void onSceneLoad() override;
		void onSceneLeave() override;

		void processPackets(const std::vector<std::unique_ptr<net::Packet>>& packets) override;
	};
}