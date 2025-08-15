#include "MovementComponent.hpp"
#include "StrategyFactory.hpp"

namespace royale
{
	MovementComponent::MovementComponent(double speed, MovementStrategy* strategy)
		:
		mSpeed{ speed },
		mStrategy{ strategy }
	{
	}

	MovementComponent::~MovementComponent()
	{
		//delete mStrategy;
	}

	void MovementComponent::update(GameObject& gameObject)
	{
		// impl
	}

	std::unique_ptr<Component> MovementComponent::clone() const
	{
		MovementComponent copy = { mSpeed, mStrategy};
		return std::make_unique<MovementComponent>(copy);
	}

	std::unique_ptr<MovementComponent> MovementComponent::fromJson(json& data)
	{
		int speed = data["speed"];
		MovementStrategy* movementS = StrategyFactory::fromString<MovementStrategy>(data["strategy"]);

		return std::make_unique<MovementComponent>(speed, movementS);
	}

}