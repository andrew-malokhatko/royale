#pragma once

#include "GameContext.hpp"
#include "Tower.hpp"
#include "config.hpp"
#include <vector>

namespace royale
{
	class TowerManager
	{
		std::vector<Tower> mTowers {};

	public:
		TowerManager() = default;

		void placeTowers(GameContext& context);
		void resetTowers();

		const std::vector<Tower>& getTowers() const;
		std::vector<Tower>& getTowers();

	};
}