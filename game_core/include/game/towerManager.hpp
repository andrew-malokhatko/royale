#pragma once

#include "GameContext.hpp"
#include "Tower.hpp"
#include "config.hpp"
#include <unordered_map>
#include <ranges>

namespace royale
{
	class TowerManager
	{
		// Use map for optimal iteration and access
		std::unordered_map<GameObjectId, Tower> mTowers;

	public:
		//using tower_iterator = std::map<GameObjectId, Tower>::iterator;
		//using tower_const_iterator = std::map<GameObjectId, Tower>::const_iterator;

	public:
		TowerManager() = default;

		void placeTowers(GameContext& context);
		void resetTowers();

		const Tower* getTowerById(GameObjectId id) const;
		Tower* getTowerById(GameObjectId id);

		const std::unordered_map<GameObjectId, Tower>& getTowers() const;
		std::unordered_map<GameObjectId, Tower>& getTowers();

		void removeTower(GameObjectId towerId);
		

		void update();

		//std::pair<TowerManager::tower_const_iterator, TowerManager::tower_const_iterator> getAllTowers() const;

		//auto getAllTowers()
		//{
		//	return std::views::all(mTowers);
		//}
	};
}