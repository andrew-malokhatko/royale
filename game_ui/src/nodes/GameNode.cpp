#include "GameNode.hpp"
#include "Entity.hpp"

namespace ui
{
	GameNode::GameNode(Rectangle rectangle, const royale::Game& game)
		:
		Node(rectangle),
		mGame{game}
	{
	}

	static Vector2 toRayVec2(royale::Vector2 vec)
	{
		return Vector2{ static_cast<float>(vec.x), static_cast<float>(vec.y) };
	}

	void GameNode::drawSelf() const
	{
		Vector2 fieldSize = toRayVec2(mGame.getFieldSize());

		royale::Vector2 tileSize = royale::Vector2{ mRec.width / fieldSize.x, mRec.height / fieldSize.y };

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
		static const float textureScale = 2.0;
		const auto& entities = mGame.getEntities();
		for (const auto& [id, entity] : entities)
		{
			royale::Vector2 pos = entity.getPosition();
			royale::Vector2 size = entity.getSize();

			pos.scale(tileSize);
			size.scale(tileSize);
		
			// DEBUG
			Color color = entityColors.at(entity.getType());
			DrawRectangle(pos.x, pos.y, size.x, size.y, color);

			float dstX = static_cast<float>(pos.x - size.x / textureScale);
			float dstY = static_cast<float>(pos.y - size.x / textureScale);
			float dstWidth = static_cast<float>(size.x * textureScale);
			float dstHeight = static_cast<float>(size.y * textureScale);

			const Texture2D& texture = mTextureManager.getTexture(entity.getType());
			Rectangle src = { 0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height) };
			Rectangle dst = { dstX, dstY, dstWidth, dstHeight };

			DrawTexturePro(texture, src, dst, { 0, 0 }, 0.0f, WHITE);
		}

		// draw towers
		const auto& towers = mGame.getTowers();
		for (const auto& [id, tower] : towers)
		{
			royale::Vector2 towerPos{ tower.getPosition().x * tileSize.x, tower.getPosition().y * tileSize.y };
			royale::Vector2 towerSize{ tower.getSize().x * tileSize.x, tower.getSize().y * tileSize.y };

			DrawRectangle(towerPos.x, towerPos.y, towerSize.x, towerSize.y, GRAY);
		}
	}

	void GameNode::resizeSelf(int width, int height)
	{
		royale::Vector2 fieldSize = mGame.getFieldSize();

		int maxTileWidth = width / fieldSize.x;
		int maxTileHeight = height / fieldSize.y;
		int maxTileSize = std::min(maxTileHeight, maxTileWidth);

		int finalWidth = maxTileSize * fieldSize.x;
		int finalHeight = maxTileSize * fieldSize.y;

		setSize({ static_cast<float>(finalWidth), static_cast<float>(finalHeight) });
	}


	Rectangle GameNode::getViewPort()
	{
		return mRec;
	}

	Vector2 GameNode::getLayout()
	{
		auto vec = mGame.getFieldSize();
		return { static_cast<float>(vec.x), static_cast<float>(vec.y) };
	}

	Vector2 GameNode::getTileFromPos(Vector2 pos)
	{
		Rectangle viewport = getViewPort();
		Vector2 gameSize = getLayout();

		Vector2 tileSize = { viewport.width / gameSize.x, viewport.height / gameSize.y };
		Vector2 relativeMousePos = { pos.x - viewport.x, pos.y - viewport.y };

		int ghostX = relativeMousePos.x / tileSize.x;
		int ghostY = relativeMousePos.y / tileSize.y;

		return { static_cast<float>(ghostX), static_cast<float>(ghostY) };
	}
}