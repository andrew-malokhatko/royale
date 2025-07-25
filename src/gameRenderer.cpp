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

			const std::vector<Unit*>& units = game.getUnits();
			for (Unit* unit : units)
			{
				Vector2 pos = unit->getPosition().scale(tileSize);
				Vector2 size = unit->getSize();

				Color color = unitColors.at(unit->getUnitType());

				DrawRectangle(pos.x, pos.y, size.x, size.y, color);
			}

		EndTextureMode();

		/*BeginDrawing();

		// fill in the background
		ClearBackground(BACKGROUND_COLOR);

		// draw background
		Vector2 gameResolution = game.getGameResolution();
		Vector2 fieldSize = game.getFieldSize();

		int tileSize = game.getTileSize();
		int rows = fieldSize.y / tileSize;
		int cols = fieldSize.x / tileSize;
		int fieldOffsetX = (gameResolution.x - fieldSize.x) / 2;
		int fieldOffsetY = (gameResolution.y - fieldSize.y) / 10;

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				bool isDark = (col + row) % 2 == 1;
				Color tileColor = isDark ? DARKGREEN : GREEN;

				int tileX = col * tileSize + fieldOffsetX;
				int tileY = row * tileSize + fieldOffsetY;

				DrawRectangle(tileX, tileY, tileSize, tileSize, tileColor);
			}
		}

		// draw available cards

		int controlPanelX = 0;
		int controlPanelY = fieldSize.y + fieldOffsetY * 2;
		int controlPanelWidth = gameResolution.x;
		int controlPanelHeight = gameResolution.y - fieldSize.y - (fieldOffsetY * 2);
		Color controlPanelColor = LIGHTGRAY;

		DrawRectangle(controlPanelX, controlPanelY, controlPanelWidth, controlPanelHeight, controlPanelColor);

		int cardWidth = controlPanelWidth / 4 - fieldOffsetX;
		int cardHeight = controlPanelHeight - fieldOffsetY * 2;
		int cardY = controlPanelY + fieldOffsetY;
		Color cardColor = GRAY;

		for (int i = 0; i < 4; i++)
		{
			int cardX = controlPanelX + i * cardWidth + (i + 0.5) * fieldOffsetX;
			DrawRectangle(cardX, cardY, cardWidth, cardHeight, cardColor);
		}
		
		EndDrawing();*/
	}
}