#pragma once

#include "raylib.h"

class EntityTexture
{
	Texture2D mForward;
	Texture2D mBack;

public:
	EntityTexture(Texture2D forward, Texture2D back);
	EntityTexture(Texture2D texture);
	EntityTexture(Texture2D&& forward, Texture2D&& back);
	EntityTexture(Texture2D&& texture);

	EntityTexture(const EntityTexture& entityTexture) = delete;
	EntityTexture& operator=(const EntityTexture& rhs) = delete;

	EntityTexture(EntityTexture&& entityTexture) noexcept;	// move ctor
	EntityTexture& operator=(EntityTexture&& rhs) noexcept;	// move assign
	bool operator==(const EntityTexture& rhs) const;		// == op

	~EntityTexture();

	void resize(int width, int height);
	const Texture2D& getTexture(bool forward = true) const;
};