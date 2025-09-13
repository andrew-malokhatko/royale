#include "EntityTextureManager.hpp"
#include "EntityData.hpp"
#include <string>
#include <format>
#include <cassert>

EntityTextureManager::EntityTextureManager()
{
	if (InstanceCount == 0)
		LoadImages();

	InstanceCount++;
}

EntityTextureManager::~EntityTextureManager()
{
	InstanceCount--;

	if (InstanceCount == 0)
		UnloadImages();
}

void EntityTextureManager::LoadImages()
{
	Fronts.reserve(royale::ENTITY_DATA.size());
	Backs.reserve(royale::ENTITY_DATA.size());

	LoadedImages = std::async(std::launch::async, []() {
		for (const auto& [entity, name] : royale::STRING_FROM_ENTITY)
		{
			std::string fwd_path = std::format("assets/characters/{}/{}_forward.png", name, name);
			std::string bwd_path = std::format("assets/characters/{}/{}_back.png", name, name);

			Image forward = LoadImage(fwd_path.c_str());
			Image back = LoadImage(bwd_path.c_str());

			Fronts[entity] = forward;
			Backs[entity] = back;
		}
	});
}

void EntityTextureManager::UnloadImages()
{
	for (auto& [entity, image]: Fronts)
	{
		UnloadImage(image);
	}

	for (auto& [entity, image] : Backs)
	{
		UnloadImage(image);
	}

	Fronts.clear();
	Backs.clear();
}

void EntityTextureManager::loadTextures(const std::vector<royale::EntityType>& entities)
{
	assert(LoadedImages.valid());
	LoadedImages.wait();

	for (auto& entity : entities)
	{
		if (!Textures.contains(entity))
		{
			assert(Backs.contains(entity));
			assert(Fronts.contains(entity));

			const Image& back = Backs.at(entity);
			const Image& front = Fronts.at(entity);

			EntityTexture texture{ front, back };
			Textures.emplace(entity, std::move(texture));
		}
	}
}

const Texture2D& EntityTextureManager::getTexture(royale::EntityType type, bool forward) const
{
	assert(LoadedImages.valid());
	LoadedImages.wait();

	assert(Textures.contains(type));

	return Textures.at(type).getTexture(forward);
}

