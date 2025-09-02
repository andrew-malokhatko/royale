#pragma once

#include "Node.hpp"
#include "raylib.h"
#include <string>

namespace ui
{
	class TextureComponent : public Node
	{
	protected:
		Texture2D mTexture;

	public:
		TextureComponent(Rectangle rec, std::string textureName);
		virtual ~TextureComponent();

		void drawSelf() const override;
		void resizeSelf(int width, int height) override;

		static Texture2D TextureFromString(const std::string& str);
	};
}