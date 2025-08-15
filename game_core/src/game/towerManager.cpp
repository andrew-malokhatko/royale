//#include "towerManager.hpp"
//
//namespace royale
//{
//	TowerManager::TowerManager()
//	{
//		Tower leftArcherTowerTop{ Config::LEFT_TOWER_POSITION, Config::ARCHER_TOWER_SIZE, 1, 1 };
//		Tower rightArcherTowerTop{ Config::RIGHT_TOWER_POSITION, Config::ARCHER_TOWER_SIZE, 1, 1 };
//		Tower kingTowerTop{ Config::KING_TOWER_POSITION, Config::KING_TOWER_SIZE, 2, 1 };
//
//		Vector2 leftTowerBottomVec{ Config::LEFT_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::LEFT_TOWER_POSITION.y - Config::ARCHER_TOWER_SIZE.y };
//		Vector2 rightTowerBottomVec{ Config::RIGHT_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::RIGHT_TOWER_POSITION.y - Config::ARCHER_TOWER_SIZE.y };
//		Vector2 kingTowerBottomVec{ Config::KING_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::KING_TOWER_POSITION.y - Config::KING_TOWER_SIZE.y };
//
//		Tower leftArcherTowerBottom{ leftTowerBottomVec, Config::ARCHER_TOWER_SIZE, 1, 1 };
//		Tower rightArcherTowerBottom{ rightTowerBottomVec, Config::ARCHER_TOWER_SIZE, 1, 1 };
//		Tower kingTowerBottom{ kingTowerBottomVec, Config::KING_TOWER_SIZE, 2, 1 };
//
//		static_assert(Config::TOWER_COUNT == 6);
//
//		mTowers[0] = std::move(leftArcherTowerTop);
//		mTowers[1] = std::move(rightArcherTowerTop);
//		mTowers[2] = std::move(kingTowerTop);
//		mTowers[3] = std::move(leftArcherTowerBottom);
//		mTowers[4] = std::move(rightArcherTowerBottom);
//		mTowers[5] = std::move(kingTowerBottom);
//	}
//
//	const std::array<Tower, Config::TOWER_COUNT>& TowerManager::getTowers() const
//	{
//		return mTowers;
//	}
//}