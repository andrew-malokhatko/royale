#include "gameRenderer.hpp"
#include "Entity.hpp"

GameRenderer::GameRenderer()
{

}

GameRenderer::~GameRenderer()
{

}

Vector2 toRayVec2(royale::Vector2 vec)
{
	return Vector2{ static_cast<float>(vec.x), static_cast<float>(vec.y) };
}

void GameRenderer::render(const royale::Game& game, RenderTexture2D& target)
{
	BeginTextureMode(target);

	Vector2 fieldSize = toRayVec2(game.getFieldSize());

	float width = target.texture.width;
	float height = target.texture.height;

	royale::Vector2 tileSize = royale::Vector2{ width / fieldSize.x, height / fieldSize.y };

	// draw field
	for (int row = 0; row < fieldSize.y; row++)
	{
		for (int col = 0; col < fieldSize.x; col++)
		{
			bool isDark = (col + row) % 2 == 1;
			Color tileColor = isDark ? DARKGREEN : GREEN;

			int tileX = col * tileSize.x;
			int tileY = row * tileSize.y;

			DrawRectangle(tileX, tileY, tileSize.x, tileSize.y, tileColor);
		}
	}
	
	// draw entities
	const auto& entities = game.getEntities();
	for (const auto& [id, entity] : entities)
	{
		royale::Vector2 pos = entity.getPosition();
		royale::Vector2 size = entity.getSize();

		pos.scale(tileSize);
		size.scale(tileSize);

		Color color = entityColors.at(entity.getType());
		DrawRectangle(pos.x, pos.y, size.x, size.y, color);
	}

	// draw towers
	const auto& towers = game.getTowers();
	for (const auto& [id, tower] : towers)
	{
		royale::Vector2 towerPos{ tower.getPosition().x * tileSize.x, tower.getPosition().y * tileSize.y };
		royale::Vector2 towerSize{ tower.getSize().x * tileSize.x, tower.getSize().y * tileSize.y };

		DrawRectangle(towerPos.x, towerPos.y, towerSize.x, towerSize.y, TowerColor);
	}

	EndTextureMode();
}
