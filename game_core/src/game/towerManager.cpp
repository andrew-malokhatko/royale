#include "TowerManager.hpp"
#include "HealthComponent.hpp"

namespace royale
{
	void TowerManager::placeTowers(GameContext& context)
	{
		Tower leftArcherTowerTop{ EntityType::ArcherTower, Config::LEFT_TOWER_POSITION, Config::ARCHER_TOWER_SIZE, context };
		Tower rightArcherTowerTop{ EntityType::ArcherTower, Config::RIGHT_TOWER_POSITION, Config::ARCHER_TOWER_SIZE, context };
		Tower kingTowerTop{ EntityType::KingTower, Config::KING_TOWER_POSITION, Config::KING_TOWER_SIZE, context };

		Vector2 leftTowerBottomVec{ Config::LEFT_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::LEFT_TOWER_POSITION.y - Config::ARCHER_TOWER_SIZE.y };
		Vector2 rightTowerBottomVec{ Config::RIGHT_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::RIGHT_TOWER_POSITION.y - Config::ARCHER_TOWER_SIZE.y };
		Vector2 kingTowerBottomVec{ Config::KING_TOWER_POSITION.x, Config::FIELD_HEIGHT - Config::KING_TOWER_POSITION.y - Config::KING_TOWER_SIZE.y };

		Tower leftArcherTowerBottom{ EntityType::ArcherTower, leftTowerBottomVec, Config::ARCHER_TOWER_SIZE, context };
		Tower rightArcherTowerBottom{ EntityType::ArcherTower, rightTowerBottomVec, Config::ARCHER_TOWER_SIZE, context };
		Tower kingTowerBottom{ EntityType::KingTower, kingTowerBottomVec, Config::KING_TOWER_SIZE, context };

		static_assert(Config::TOWER_COUNT == 6);

		mTowers.emplace(leftArcherTowerTop.getId(), std::move(leftArcherTowerTop));
		mTowers.emplace(rightArcherTowerTop.getId(), std::move(rightArcherTowerTop));
		mTowers.emplace(kingTowerTop.getId(), std::move(kingTowerTop));

		mTowers.emplace(leftArcherTowerBottom.getId(), std::move(leftArcherTowerBottom));
		mTowers.emplace(rightArcherTowerBottom.getId(), std::move(rightArcherTowerBottom));
		mTowers.emplace(kingTowerBottom.getId(), std::move(kingTowerBottom));
	}

	void TowerManager::resetTowers()
	{
		mTowers.clear();
	}

	const Tower* TowerManager::getTowerById(GameObjectId id) const
	{
		if (mTowers.contains(id))
		{
			return &mTowers.at(id);
		}
		return nullptr;
	}

	Tower* TowerManager::getTowerById(GameObjectId id)
	{
		if (mTowers.contains(id))
		{
			return &mTowers.at(id);
		}
		return nullptr;
	}

	const std::unordered_map<GameObjectId, Tower>& TowerManager::getTowers() const
	{
		return mTowers;
	}

	std::unordered_map<GameObjectId, Tower>& TowerManager::getTowers()
	{
		return mTowers;
	}

	void TowerManager::removeTower(GameObjectId towerId)
	{
		mTowers.erase(towerId);
	}

	void TowerManager::update()
	{

		for (auto& [id, tower] : mTowers)
		{
			tower.update();
		}

	}

	//std::pair<TowerManager::tower_const_iterator, TowerManager::tower_const_iterator> TowerManager::getAllTowers() const
	//{
	//	return {mTowers.begin(), mTowers.end()};
	//}
}