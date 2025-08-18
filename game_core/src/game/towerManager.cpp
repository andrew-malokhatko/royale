#include "TowerManager.hpp"

namespace royale
{
	void TowerManager::placeTowers(GameContext& context)
	{
		Tower leftArcherTowerTop{ Config::LEFT_TOWER_POSITION, Config::ARCHER_TOWER_SIZE, 1, 1, context };
		Tower rightArcherTowerTop{ Config::RIGHT_TOWER_POSITION, Config::ARCHER_TOWER_SIZE, 1, 1, context };
		Tower kingTowerTop{ Config::KING_TOWER_POSITION, Config::KING_TOWER_SIZE, 2, 1, context };

		Vector2 leftTowerBottomVec{ Config::LEFT_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::LEFT_TOWER_POSITION.y - Config::ARCHER_TOWER_SIZE.y };
		Vector2 rightTowerBottomVec{ Config::RIGHT_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::RIGHT_TOWER_POSITION.y - Config::ARCHER_TOWER_SIZE.y };
		Vector2 kingTowerBottomVec{ Config::KING_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::KING_TOWER_POSITION.y - Config::KING_TOWER_SIZE.y };

		Tower leftArcherTowerBottom{ leftTowerBottomVec, Config::ARCHER_TOWER_SIZE, 1, 1, context };
		Tower rightArcherTowerBottom{ rightTowerBottomVec, Config::ARCHER_TOWER_SIZE, 1, 1, context };
		Tower kingTowerBottom{ kingTowerBottomVec, Config::KING_TOWER_SIZE, 2, 1, context };

		static_assert(Config::TOWER_COUNT == 6);

		mTowers.emplace_back(std::move(leftArcherTowerTop));
		mTowers.emplace_back(std::move(rightArcherTowerTop));
		mTowers.emplace_back(std::move(kingTowerTop));

		mTowers.emplace_back(std::move(leftArcherTowerBottom));
		mTowers.emplace_back(std::move(rightArcherTowerBottom));
		mTowers.emplace_back(std::move(kingTowerBottom));
	}

	void TowerManager::resetTowers()
	{
		mTowers.clear();
	}

	const std::vector<Tower>& TowerManager::getTowers() const
	{
		return mTowers;
	}

	std::vector<Tower>& TowerManager::getTowers()
	{
		return mTowers;
	}
}