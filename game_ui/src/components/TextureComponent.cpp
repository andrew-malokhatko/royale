#include "components/TextureComponent.hpp"
#include <format>

namespace ui
{
	TextureComponent::TextureComponent(Rectangle rec, std::string textureName)
		:
		Node(rec),
		mTexture{TextureFromString(textureName)}
	{
	}

	TextureComponent::~TextureComponent()
	{
		UnloadTexture(mTexture);
	}

	void TextureComponent::drawSelf() const
	{
		Rectangle source = { 0, 0, mRec.width, mRec.height };
		Vector2 position = { 0, 0 };
		DrawTextureRec(mTexture, source, position, WHITE);
	}

	void TextureComponent::resizeSelf(int width, int height)
	{
		setSize({ static_cast<float>(width), static_cast<float>(height) });

		Image image = LoadImageFromTexture(mTexture);
		ImageResize(&image, mRec.width, mRec.height);

		UnloadTexture(mTexture);
		mTexture = LoadTextureFromImage(image);

		UnloadImage(image);
	}

	Texture2D TextureComponent::TextureFromString(const std::string& str)
	{
		std::string path = std::format("assets/{}.png", str);
		return LoadTexture(path.c_str());
	}
}