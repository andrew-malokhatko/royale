#include "gameRenderer.hpp"

namespace royale
{
	GameRenderer::GameRenderer()
	{
		
	}

	GameRenderer::~GameRenderer()
	{

	}

	void GameRenderer::render(const Game& game, RenderTexture2D& target)
	{
		BeginTextureMode(target);

			Vector2 fieldSize = game.getFieldSize();

			double width = target.texture.width;
			double height = target.texture.height;

			Vector2 tileSize = Vector2{ width / fieldSize.x, height / fieldSize.y };

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

			// draw units
			const std::vector<Unit*>& units = game.getUnits();
			for (Unit* unit : units)
			{
				Vector2 pos = unit->getPosition();
				pos.scale(tileSize);
				Vector2 size = unit->getSize();
				Color color = unitColors.at(unit->getUnitType());

				DrawRectangle(pos.x, pos.y, size.x, size.y, color);
			}

			// draw towers
			auto towers = game.getTowers();
			for (Tower& tower : towers)
			{
				Vector2 towerPos{ tower.getPosition().x * tileSize.x, tower.getPosition().y * tileSize.y };
				Vector2 towerSize{ tower.getSize().x * tileSize.x, tower.getSize().y * tileSize.y };

				DrawRectangle(towerPos.x, towerPos.y, towerSize.x, towerSize.y, TowerColor);
			}

		EndTextureMode();
	}
}