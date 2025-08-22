#include "EntityTextureManager.hpp"
#include "EntityData.hpp"
#include <string>
#include <format>


void EntityTextureManager::LoadTextures()
{
	mTextures.reserve(royale::ENTITY_DATA.size());

	for (const auto& [entity, name] : royale::STRING_FROM_ENTITY)
	{
		std::string fwd_path = std::format("assets/characters/{}/{}_forward.png", name, name);
		std::string bwd_path = std::format("assets/characters/{}/{}_back.png", name, name);

		Texture2D forward = LoadTexture(fwd_path.c_str());
		Texture2D back = LoadTexture(bwd_path.c_str());

		EntityTexture texture{ forward, back };

		mTextures.emplace(entity, std::move(texture));
	}
}

void EntityTextureManager::resize(int width, int height)
{
	for (auto& [entity, texture] : mTextures)
	{
		texture.resize(width, height);
	}
}

const Texture2D& EntityTextureManager::getTexture(royale::EntityType type, bool forward) const
{
	return mTextures.at(type).getTexture(forward);
}

