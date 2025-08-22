#pragma once

#include "raylib.h"
#include "EntityType.hpp"
#include "EntityTexture.hpp"
#include <unordered_map>

class EntityTextureManager
{
private:
	std::unordered_map<royale::EntityType, EntityTexture> mTextures{};

public:
	EntityTextureManager() = default;

	void LoadTextures();
	void resize(int width, int height);

	const Texture2D& getTexture(royale::EntityType type, bool forward = true) const;
};