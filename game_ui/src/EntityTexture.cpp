#include "EntityTexture.hpp"
#include <utility>

EntityTexture::EntityTexture(Texture2D forward, Texture2D back)
	:
	mForward{ forward },
	mBack{ back }
{
}

EntityTexture::EntityTexture(Texture2D texture)
	:
	mForward{texture},
	mBack{ texture }
{
}

EntityTexture::EntityTexture(Texture2D&& forward, Texture2D&& back)
	:
	mForward{ std::move(forward) },
	mBack{ std::move(back) }
{
	forward.id = 0;
	back.id = 0;
}

EntityTexture::EntityTexture(Texture2D&& texture)
	:
	mForward{ std::move(texture) },
	mBack{ std::move(texture) }
{
	texture.id = 0;
}

EntityTexture::EntityTexture(EntityTexture&& entityTexture) noexcept
	:
	mForward{ std::move(entityTexture.mForward) },
	mBack{ std::move(entityTexture.mBack) }
{
	entityTexture.mForward.id = 0;
	entityTexture.mBack.id = 0;
}

EntityTexture& EntityTexture::operator=(EntityTexture&& rhs) noexcept
{
	if (this == &rhs)
	{
		return *this;
	}

	mForward = std::move(rhs.mForward);
	mBack = std::move(rhs.mBack);

	rhs.mForward.id = 0;
	rhs.mBack.id = 0;

	return *this;
}

bool EntityTexture::operator==(const EntityTexture& rhs) const
{
	return mForward.id == rhs.mForward.id && mBack.id == rhs.mBack.id;
}

EntityTexture::~EntityTexture()
{
	UnloadTexture(mForward);
	UnloadTexture(mBack);
}

void EntityTexture::resize(int width, int height)
{

}

const Texture2D& EntityTexture::getTexture(bool forward) const
{
	return forward ? mForward : mBack;
}