#pragma once

#include "AttackComponent.hpp"
#include "StrategyFactory.hpp"

namespace royale
{
	AttackComponent::AttackComponent(int damage, double speed, double range, TargetType targetType, AttackStrategy* strategy)
		:
		mDamage{damage},
		mSpeed{speed},
		mRange{range},
		mStrategy{strategy}
	{
	}

	AttackComponent::~AttackComponent()
	{
		//delete mStrategy;
	}

	void AttackComponent::update(GameObject& gameObject)
	{
		//mStrategy.attack();
	}

	std::unique_ptr<Component> AttackComponent::clone() const
	{
		AttackComponent copy = { mDamage, mSpeed, mRange, mTargetType, mStrategy };
		return std::make_unique<AttackComponent>(copy);
	}
	
	std::unique_ptr<AttackComponent> AttackComponent::fromJson(json& data)
	{
		int damage = data["damage"];
		double speed = data["speed"];
		double range = data["range"];

		TargetType targetT = targetFromString(data["target"]);
        AttackStrategy* attackS = StrategyFactory::fromString<AttackStrategy>(data["strategy"]);

		return std::make_unique<AttackComponent>(damage, speed, range, targetT, attackS);
	}
}
