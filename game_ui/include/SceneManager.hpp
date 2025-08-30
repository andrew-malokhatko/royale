#pragma once

#include <string>

namespace ui
{
	class SceneManager
	{
	public:

		//
		//	Displays new scene by the given name
		//
		virtual void setScene(const std::string& sceneName) = 0;
	};
}