#pragma once

#include "tower.hpp"
#include "config.hpp"
#include <vector>

namespace royale
{
	class TowerManager
	{
		std::vector<Tower> mTowers {};

	public:
		TowerManager() = default;

		void placeTowers(Game& context);
		void resetTowers();
		const std::vector<Tower>& getTowers() const;
	};
}