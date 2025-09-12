#include "components/LoadingIcon.hpp"

namespace ui
{
	LoadingIcon::LoadingIcon(Rectangle rec, std::string textureName, float rotationSpeed)
		:
		TextureComponent(rec, textureName),
		mRotationSpeed{rotationSpeed}
	{
	}

	void LoadingIcon::drawSelf() const
	{
		Rectangle source = { 0, 0, mRec.width, mRec.height };
		Rectangle dest = { 0, 0, mRec.width, mRec.height };
		Vector2 origin = { mRec.width / 2, mRec.height / 2 };

		DrawTexturePro(mTexture, source, dest, origin, mRotation, WHITE);
	}

	void LoadingIcon::updateSelf()
	{
		mRotation += mRotationSpeed;
		if (mRotation >= 360.0f)
		{
			mRotation -= 360.0f;
		}
	}
}

