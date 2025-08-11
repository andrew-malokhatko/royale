#pragma once

#include "tower.hpp"
#include "config.hpp"
#include <array>

namespace royale
{
	class TowerManager
	{
		std::array<Tower, Config::TOWER_COUNT> mTowers {};

	public:
		TowerManager();
		const std::array<Tower, Config::TOWER_COUNT>& getTowers() const;
	};
}