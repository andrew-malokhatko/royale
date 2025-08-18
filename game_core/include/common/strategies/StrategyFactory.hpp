#pragma once
#include <stdexcept>

#include "AttackStrategy.hpp"
#include "HealthStrategy.hpp"
#include "MovementStrategy.hpp"

// attacks strategies
#include "attack/ArrowAttackStrategy.hpp"
#include "attack/MeleeAttackStrategy.hpp"

// health strategies
#include "health/BaseHealthStrategy.hpp"

// movement strategies
#include "movement/AccelerateMovementStrategy.hpp"
#include "movement/GroundMovementStrategy.hpp"

namespace royale
{
	class StrategyFactory
	{
	public:
		template<typename T>
		static T* fromString(const std::string& str);

		template<>
		static AttackStrategy* fromString(const std::string& str)
		{
			if (str == "arrow")	return new ArrowAttackStrategy();
			if (str == "melee") return new MeleeAttackStrategy();

			throw std::invalid_argument("Invalid AttackStrategy string: " + str);
		}

		template<>
		static HealthStrategy* fromString(const std::string& str)
		{
			if (str == "base") return new BaseHealthStrategy();

			throw std::invalid_argument("Invalid HealthStrategy string: " + str);
		}

		template<>
		static MovementStrategy* fromString(const std::string& str)
		{
			if (str == "ground")			return new GroundMovementStrategy();
			if (str == "accelerate")		return new AccelerateMovementStrategy();

			throw std::invalid_argument("Invalid MovementStrategy string: " + str);
		}
	};
}