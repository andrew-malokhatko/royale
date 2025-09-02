#pragma once

#include "components/TextureComponent.hpp"

namespace ui
{
	class LoadingIcon : public TextureComponent
	{
		float mRotation = 0.0f;
		float mRotationSpeed = 0.0f;

	public:
		LoadingIcon(Rectangle rec, std::string textureName, float rotationSpeed);

		void drawSelf() const override;
		void updateSelf() override;
	};
}