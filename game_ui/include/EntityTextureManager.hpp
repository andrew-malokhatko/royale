#pragma once

#include "raylib.h"
#include "EntityType.hpp"
#include "EntityTexture.hpp"
#include <unordered_map>
#include <future>

class EntityTextureManager
{
private:
	inline static size_t InstanceCount = 0;
	inline static std::unordered_map<royale::EntityType, Image> Fronts {};
	inline static std::unordered_map<royale::EntityType, Image> Backs {};
	inline static std::future<void> LoadedImages {};

	inline static std::unordered_map<royale::EntityType, EntityTexture> Textures {};

	static void LoadImages();
	static void UnloadImages();

public: 
	EntityTextureManager();
	~EntityTextureManager();

	void loadTextures(const std::vector<royale::EntityType>& entities);
	const Texture2D& getTexture(royale::EntityType type, bool forward = true) const;
};