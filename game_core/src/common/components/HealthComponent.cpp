#include "HealthComponent.hpp"
#include "StrategyFactory.hpp"
#include <algorithm>

namespace royale
{
	HealthComponent::HealthComponent(int health, int maxHealth, HealthStrategy* healthStrategy)
		:
		mHealth{ health },
		mMaxHealth{ maxHealth },
		mStrategy{ healthStrategy }
	{
	}

	HealthComponent::~HealthComponent()
	{
		//delete mStrategy;
	}

	void HealthComponent::update(GameObject& gameObject)
	{
		mStrategy->update(gameObject, *this);
	}

	std::unique_ptr<Component> HealthComponent::clone() const
	{
		HealthComponent copy = { mHealth, mMaxHealth, mStrategy };
		return std::make_unique<HealthComponent>(copy);
	}

	void HealthComponent::takeDamage(int damage)
	{
		mHealth -= damage;
	}

	void HealthComponent::heal(int health)
	{
		mHealth = std::min(mHealth + health, mMaxHealth);
	}

	double HealthComponent::getHealth() const
	{
		return mHealth;
	}

	std::unique_ptr<HealthComponent> HealthComponent::fromJson(json& data)
	{
		int health = data["health"];
		int maxHealth = health; 
		HealthStrategy* healthStrategy = StrategyFactory::fromString<HealthStrategy>(data["strategy"]);

		return std::move(std::make_unique<HealthComponent>(health, maxHealth, healthStrategy));
	}
}